// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Manager/DeckManager.h"
#include "Deck/Domain/FDeckDomain.h"
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
	
	FDeckDomain Domain(InputData);
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


bool UDeckManager::SaveDeck()
{
	if (currentDeck.GetDeckId().IsEmpty())
	{
		if (!currentDeck.SetDeckId())
		{
			UE_LOG(LogTemp,Error,TEXT("Failed To SetDeckId"));
		}
	}
	
	if (!repository.Save(currentDeck))
	{
		UE_LOG(LogTemp,Error,TEXT("Failed To SaveDeck"));
		return false;
	}

	//OnDeckListChanged.Broadcast();
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
	FDeckDomain Domain(OutData);
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

TArray<FDeckDomain> UDeckManager::GetDecks()
{
	return  Decks;
}

FDeckDomain UDeckManager::GetCurrentDeck()const
{
	return currentDeck;
}

float UDeckManager::GetcurrentDeckTotalScore() const
{
	return currentDeck.GetTotalScore();
}

void UDeckManager::CreateDeck()
{
	currentDeck = FDeckDomain();
}

void UDeckManager::UpdateStatCurrentDeck(EDeckStatType StatType, float StatScore)
{
	if (!currentDeck.SetStatScore(StatType, StatScore))
	{
		// 추후 에러창 
		UE_LOG(LogTemp,Error, 
			TEXT("Failed to update stat. Type: %d, Score: %.2f"),
			static_cast<int32>(StatType),
			StatScore);
	}
	OnDeckUpdate.Broadcast();
}

void UDeckManager::UpdateFieldCurrentDeck(EDeckFieldType FieldType, const FString& Field)
{
	if (!currentDeck.SetField(FieldType,Field))
	{
		UE_LOG(LogTemp,Error, 
			TEXT("Failed to update Field. Type: %s"),*Field);
	}
}

void UDeckManager::UpdateImagePath(const FString& Path)
{
	if (!currentDeck.SetPath(Path))
	{
		UE_LOG(LogTemp,Error, 
			TEXT("Failed to update Path. Path: %s"),*Path);
	}
}

// 수정할때 사용 이때 델리게이트 만들어서 UI초기화 
void UDeckManager::EditDeck(const FString& deckId)
{
	
}

void UDeckManager::TestSave()
{	
	UE_LOG(LogTemp, Warning, TEXT("===== Current Deck ====="));

	UE_LOG(LogTemp, Warning, TEXT("DeckName : %s"),
		*currentDeck.GetField(EDeckFieldType::DECKNAME));
	
	UE_LOG(LogTemp, Warning, TEXT("DeckOwner : %s"),
		 *currentDeck.GetField(EDeckFieldType::OWNER));

	UE_LOG(LogTemp, Warning, TEXT("Comment : %s"),
		*currentDeck.GetField(EDeckFieldType::COMMENT));
	
	UE_LOG(LogTemp,Warning,TEXT("ImagePath : %s"),
		*currentDeck.GetImagePath());

	UE_LOG(LogTemp, Warning, TEXT("Deployment : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::DEPLOYMENT));

	UE_LOG(LogTemp, Warning, TEXT("Breakthrough : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::BREAKTHROUGH));

	UE_LOG(LogTemp, Warning, TEXT("Retention : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::RETENTION));

	UE_LOG(LogTemp, Warning, TEXT("Recovery : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::RECOVERY));

	UE_LOG(LogTemp, Warning, TEXT("Control : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::CONTROL));

	UE_LOG(LogTemp, Warning, TEXT("Flexibility : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::FLEXIBILITY));

	UE_LOG(LogTemp, Warning, TEXT("BasePower : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::BASEPOWER));

	UE_LOG(LogTemp, Warning, TEXT("RelativeA : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::RELATIVEA));

	UE_LOG(LogTemp, Warning, TEXT("RelativeB : %.2f"),
		currentDeck.GetStatScore(EDeckStatType::RELATIVEB));

	UE_LOG(LogTemp, Warning, TEXT("TotalScore : %.2f"),
		currentDeck.GetTotalScore());

	UE_LOG(LogTemp, Warning, TEXT("========================"));
}


