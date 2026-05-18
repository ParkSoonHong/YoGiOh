// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Manager/DeckManager.h"
#include "Deck/Domain/DeckDomain.h"
#include "Deck/Repository/DeckRepository.h"

void UDeckManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

bool UDeckManager::CreateAndSaveDeck(const FDeckData& InputData, FString& OutError)
{
	FDeckData Data = InputData;

	if (Data.deckID.IsEmpty())
	{
		Data.deckID = FGuid::NewGuid().ToString(EGuidFormats::Digits);
	}
	
	DeckDomain Domain(InputData);
	if (!Domain.IsValid(OutError))
	{
		UE_LOG(LogTemp, Warning, TEXT("Deck validation failed: %s"), *OutError);
		return false;
	}

	const FString DeckDir = GetDeckDir();
	IFileManager::Get().MakeDirectory(*DeckDir, true);
	
	const FString FilePath = GetDeckFilePath(Data.deckID);
	/*
	if (!DeckRepository::SaveToJson(FilePath, Domain.ToSaveData()))
	{
		OutError = TEXT("덱 저장 실패");
		return false;
	}
	*/
	NotifyDeckListChanged();
	UE_LOG(LogTemp, Log, TEXT("Deck saved successfully: %s"), *FilePath);
	return true;
}


bool UDeckManager::SaveDeck(FString& OutError, const FDeckData& Data)
{
	FDeckData SaveData = Data;

	if (SaveData.deckID.IsEmpty())
	{
		SaveData.deckID = FGuid::NewGuid().ToString();
	}

	const FString Path = GetDeckFilePath(SaveData.deckID);

	/*
	if (!DeckRepository::SaveToJson(Path, SaveData))
	{
		OutError = TEXT("덱 저장 실패");
		return false;
	}
*/
	OnDeckListChanged.Broadcast();
	return true;
}

bool UDeckManager::LoadDeck(const FString& FilePath, FDeckData& OutData)
{
	/*
	if (!DeckRepository::LoadFromJson(FilePath, OutData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load deck from %s"), *FilePath);
		return false;
	}
	*/
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
    		FDeckData Data;
    		if (LoadDeck(Dir / File, Data))
    		{
    			//Decks.Add(Data);
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

TArray<DeckDomain> UDeckManager::GetDecks()
{
	return  Decks;
}

DeckDomain UDeckManager::GetCurrentDeck()const
{
	return currentDeck;
}

void UDeckManager::CurrentBackDeck() 
{
}

void UDeckManager::createDeck()
{
	currentDeck = DeckDomain();
}

void UDeckManager::EditDeck(const FString& DeckId)
{
	
}


