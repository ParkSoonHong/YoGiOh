// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Manager/DeckManager.h"
#include "Deck/Domain/FDeckDomain.h"
#include "Deck/Repository/DeckRepository.h"

void UDeckManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (!LoadAllDecks())
	{
		UE_LOG(LogTemp, Error, TEXT("Decks not loaded"));
	}
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

// 전체 불러오기
bool UDeckManager::LoadAllDecks()
{
	if (!repository.LoadAll(Decks))
	{
		UE_LOG(LogTemp,Error,TEXT("LoadAll Failed"));
		return false;
	}
	
	for (FDeckDomain Deck : Decks)
	{
		TestLoad(Deck);
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
	
	const FString FilePath = repository.GetDeckFilePath(currentDeck);

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

void UDeckManager::NotifyDeckListChanged()
{
	OnDeckListChanged.Broadcast();
}

TArray<FDeckDomain> UDeckManager::GetDecks() const
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
void UDeckManager::UpdateDeck(const FString& deckId)
{
	if (!FindDeck(deckId,currentDeck))
	{
		UE_LOG(LogTemp,Warning,TEXT("Failed UpdateDeck"));
		return;
	}
	// UI 수정
}

void UDeckManager::TestLoad(FDeckDomain Domain)
{	
	UE_LOG(LogTemp, Warning, TEXT("===== Current Deck ====="));

	UE_LOG(LogTemp, Warning, TEXT("DeckName : %s"),
		*Domain.GetField(EDeckFieldType::DECKNAME));
	
	UE_LOG(LogTemp, Warning, TEXT("DeckOwner : %s"),
		 *Domain.GetField(EDeckFieldType::OWNER));

	UE_LOG(LogTemp, Warning, TEXT("Comment : %s"),
		*Domain.GetField(EDeckFieldType::COMMENT));
	
	UE_LOG(LogTemp,Warning,TEXT("ImagePath : %s"),
		*Domain.GetImagePath());

	UE_LOG(LogTemp, Warning, TEXT("Deployment : %.2f"),
		Domain.GetStatScore(EDeckStatType::DEPLOYMENT));

	UE_LOG(LogTemp, Warning, TEXT("Breakthrough : %.2f"),
		Domain.GetStatScore(EDeckStatType::BREAKTHROUGH));

	UE_LOG(LogTemp, Warning, TEXT("Retention : %.2f"),
		Domain.GetStatScore(EDeckStatType::RETENTION));

	UE_LOG(LogTemp, Warning, TEXT("Recovery : %.2f"),
		Domain.GetStatScore(EDeckStatType::RECOVERY));

	UE_LOG(LogTemp, Warning, TEXT("Control : %.2f"),
		Domain.GetStatScore(EDeckStatType::CONTROL));

	UE_LOG(LogTemp, Warning, TEXT("Flexibility : %.2f"),
		Domain.GetStatScore(EDeckStatType::FLEXIBILITY));

	UE_LOG(LogTemp, Warning, TEXT("BasePower : %.2f"),
		Domain.GetStatScore(EDeckStatType::BASEPOWER));

	UE_LOG(LogTemp, Warning, TEXT("RelativeA : %.2f"),
		Domain.GetStatScore(EDeckStatType::RELATIVEA));

	UE_LOG(LogTemp, Warning, TEXT("RelativeB : %.2f"),
		Domain.GetStatScore(EDeckStatType::RELATIVEB));

	UE_LOG(LogTemp, Warning, TEXT("TotalScore : %.2f"),
		Domain.GetTotalScore());

	UE_LOG(LogTemp, Warning, TEXT("========================"));
}

bool UDeckManager::FindDeck(const FString& DeckID,FDeckDomain& OutDomain)
{
	for (FDeckDomain Deck : Decks)
	{
		if (Deck.GetDeckId().Equals(DeckID))
		{
			OutDomain = Deck;
			return true;			
		}
	}
	
	return false;
}


