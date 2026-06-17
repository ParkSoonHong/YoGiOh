// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Manager/DeckManager.h"
#include "Deck/Domain/FDeckDomain.h"
#include "Deck/Repository/DeckRepository.h"
#include "Supabase/SupabaseManager.h"
#include "System/Popup/Manager/UiPopUpManager.h"
#include "User/Manager/UserManager.h"

void UDeckManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDeckManager::LoadingStart()
{
	if (USupabaseManager* supabaseMgr = GetGameInstance()->GetSubsystem<USupabaseManager>())
	{
		supabaseMgr->OnDecksLoaded.AddUObject(this, &UDeckManager::LoadingCompleted);
		supabaseMgr->OnDecksLoadFailed.AddUObject(this, &UDeckManager::LoadingFailed);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Insert User Failed"));
	}
	ServerLoadAllDeck();
}

bool UDeckManager::LocalSaveDeck()
{
	if (currentDeck.GetDeckId().IsEmpty())
	{
		if (!currentDeck.SetDeckId())
		{
			UE_LOG(LogTemp,Error,TEXT("Failed To SetDeckId"));
		}
	}
	
	if (!repository.LocalSave(currentDeck))
	{
		UE_LOG(LogTemp,Error,TEXT("Failed To LocalSave"));
		return false;
	}
	
	deckMap.Add(
			currentDeck.GetDeckId(),
			currentDeck);
	
	if (!ServerSaveDeck())
	{
		return false;
	}
	
	OnDeckListChanged.Broadcast(GetDecks());
	
	return true;
}

bool UDeckManager::LocalSaveAllDeck()
{
	TArray<FDeckDomain> deckDomains;
	deckMap.GenerateValueArray(deckDomains);

	for (const FDeckDomain& deckDomain : deckDomains)
	{
		if (!repository.LocalSave(deckDomain))
		{
			UE_LOG(LogTemp,Error,TEXT("Failed To LocalSave"));
			return false;
		}
	}
	return true;
}

// 전체 불러오기
bool UDeckManager::LocalLoadAllDecks()
{
	deckMap.Reset();
	
	if (!repository.LocalLoadAll(deckMap))
	{
		UE_LOG(LogTemp,Error,TEXT("LoadAll Failed"));
		return false;
	}

	OnDeckListChanged.Broadcast(GetDecks());
	return true;
}

bool UDeckManager::ServerLoadAllDeck()
{
	if (USupabaseManager* supabaseMgr = GetGameInstance()->GetSubsystem<USupabaseManager>())
	{
		supabaseMgr->GetDecks();
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Insert User Failed"));
	}
	return true;
}

bool UDeckManager::ServerSaveDeck()
{
	if (USupabaseManager* supabaseMgr = GetGameInstance()->GetSubsystem<USupabaseManager>())
	{
		supabaseMgr->UpsertDeck(currentDeck);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Insert User Failed"));
		return false;
	}
	return true;
}

bool UDeckManager::DeleteDeck(FString& OutError)
{
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

	//OnDeckListChanged.Broadcast();
	return true;
}

TArray<FDeckDomain> UDeckManager::GetDecks() const
{
	TArray<FDeckDomain> result;

	deckMap.GenerateValueArray(result);

	return result;
}

void UDeckManager::CreateDeck()
{
	currentDeck = FDeckDomain();
	OnDeckInitialize.Broadcast();
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
	OnDeckTotatlScoreUpdate.Broadcast();
}

void UDeckManager::UpdateFieldCurrentDeck(EDeckFieldType FieldType, const FString& Field)
{
	FString Value = Field;
	if (FieldType == EDeckFieldType::OWNERID)
	{
		if (UUserManager * UserMgr = GetGameInstance()->GetSubsystem<UUserManager>())
		{
			FString OwnerId;
			if (!UserMgr->TryGetUserIdByName(Field, OwnerId))
			{
				UE_LOG(LogTemp,Warning,TEXT("Failed TryGetUserIdByName. UserName: %s"),*Field);
				return;
			}
			
			Value = OwnerId;
		}
	}
	
	if (!currentDeck.SetField(FieldType,Value))
	{
		UE_LOG(LogTemp,Error, TEXT("Failed to update Field. Type: %s"),*Field);
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

void UDeckManager::UpdateDeck(const FString& DeckId)
{
	if (!FindDeck(DeckId,currentDeck))
	{
		UE_LOG(LogTemp,Warning,TEXT("Failed UpdateDeck"));
		return;
	}
	
	if (UUiPopUpManager * Popupmgr = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		Popupmgr->PushPopup(EUIPopUpType::TIERLISTDETAIL);
	}
	OnDeckUpdate.Broadcast();
}

void UDeckManager::ApplyFilter(const FString& FilterType)
{
}

void UDeckManager::ApplySort()
{
}

bool UDeckManager::FindDeck(const FString& DeckID,FDeckDomain& OutDomain)
{
	if (const FDeckDomain* Domain = deckMap.Find(DeckID))
	{
		OutDomain = *Domain;
		return true;
	}
	
	return false;
}

void UDeckManager::LoadingCompleted(const FDeckMap& DeckMap)
{
	deckMap = DeckMap;
	LocalSaveAllDeck();
	OnDeckLoadcompleted.Broadcast();
}

void UDeckManager::LoadingFailed()
{
	if (!LocalLoadAllDecks())
	{
		UE_LOG(LogTemp,Error,TEXT("Loading Failed"));
		return;
	}
	OnDeckLoadcompleted.Broadcast();
}
