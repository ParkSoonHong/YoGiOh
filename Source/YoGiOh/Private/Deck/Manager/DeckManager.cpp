// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Manager/DeckManager.h"
#include "Deck/Domain/DeckDomain.h"
#include "Deck/Repository/DeckRepository.h"

bool UDeckManager::CreateAndSaveDeck(const FDeckSaveData& InputData, FString& OutError)
{
	FDeckSaveData Data = InputData;

	if (Data.DeckID.IsEmpty())
	{
		Data.DeckID = FGuid::NewGuid().ToString(EGuidFormats::Digits);
	}
	
	DeckDomain Domain(InputData);
	if (!Domain.IsValid(OutError))
	{
		UE_LOG(LogTemp, Warning, TEXT("Deck validation failed: %s"), *OutError);
		return false;
	}

	const FString DeckDir = GetDeckDir();
	IFileManager::Get().MakeDirectory(*DeckDir, true);
	
	const FString FilePath = GetDeckFilePath(Data.DeckID);
	if (!DeckRepository::SaveToJson(FilePath, Domain.ToSaveData()))
	{
		OutError = TEXT("덱 저장 실패");
		return false;
	}
	
	NotifyDeckListChanged();
	UE_LOG(LogTemp, Log, TEXT("Deck saved successfully: %s"), *FilePath);
	return true;
}


bool UDeckManager::SaveDeck(FString& OutError, const FDeckSaveData& Data)
{
	FDeckSaveData SaveData = Data;

	if (SaveData.DeckID.IsEmpty())
	{
		SaveData.DeckID = FGuid::NewGuid().ToString();
	}

	const FString Path = GetDeckFilePath(SaveData.DeckID);

	if (!DeckRepository::SaveToJson(Path, SaveData))
	{
		OutError = TEXT("덱 저장 실패");
		return false;
	}

	OnDeckListChanged.Broadcast();
	return true;
}

bool UDeckManager::LoadDeck(const FString& FilePath, FDeckSaveData& OutData)
{
	if (!DeckRepository::LoadFromJson(FilePath, OutData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load deck from %s"), *FilePath);
		return false;
	}
	DeckDomain Domain(OutData);
	FString Error;
	if (!Domain.IsValid(Error))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded deck invalid: %s"), *Error);
	}
	return true;
}

// 전체 불러오기
bool UDeckManager::LoadAllDecks()
{
	const FString Dir = GetDeckDir();
    
	if (!IFileManager::Get().DirectoryExists(*Dir))
	{
		return true;
	}
    	TArray<FString> Files;
    	IFileManager::Get().FindFiles(Files, *Dir, TEXT("*.json"));
    
    	for (const FString& File : Files)
    	{
    		FDeckSaveData Data;
    		if (LoadDeck(Dir / File, Data))
    		{
    			Decks.Add(Data);
    		}
    	}
    	return true;
}

bool UDeckManager::DeleteDeck(const FString& DeckID, FString& OutError)
{
	if (DeckID.IsEmpty())
	{
		OutError = TEXT("DeckID가 비어있습니다.");
		return false;
	}
	
	const FString FilePath = GetDeckFilePath(DeckID);

	if (!IFileManager::Get().FileExists(*FilePath))
	{
		OutError = TEXT("덱 파일이 존재하지 않습니다");
		return false;
	}

	if (!IFileManager::Get().Delete(*FilePath))
	{
		OutError = TEXT("덱 삭제 실패");
		return false;
	}

	NotifyDeckListChanged();
	return true;
}

FString UDeckManager::GetDeckDir() const
{
	return FPaths::ProjectSavedDir() / TEXT("Decks");
}

FString UDeckManager::GetDeckFilePath(const FString& DeckID) const
{
	return GetDeckDir() / FString::Printf(TEXT("%s.json"), *DeckID);
}

void UDeckManager::NotifyDeckListChanged()
{
	OnDeckListChanged.Broadcast();
}

TArray<FDeckSaveData> UDeckManager::GetDecks()
{
	return  Decks;
}
