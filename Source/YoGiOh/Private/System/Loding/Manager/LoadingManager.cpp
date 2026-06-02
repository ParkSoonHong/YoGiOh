// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Loading/Manager/LoadingManager.h"

#include "Deck/Manager/DeckManager.h"
#include "System/Popup/Manager/UiPopUpManager.h"
#include "User/Manager/UserManager.h"

void ULoadingManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void ULoadingManager::LoadingStart()
{
	LoadingCount = 0;
	if (UUserManager* userMgr = GetGameInstance()->GetSubsystem<UUserManager>())
	{
		LoadingCount++;
		userMgr->LodingStart();
		userMgr->OnUserLoadcompleted.AddUObject(this, &ULoadingManager::LoadingEnd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUserManager::LodingStart()"));
	}
	
	if (UDeckManager* deckMgr = GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		LoadingCount++;
		deckMgr->LoadingStart();
		deckMgr->OnDeckLoadcompleted.AddUObject(this, &ULoadingManager::LoadingEnd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUserManager::LodingStart()"));
	}
}

void ULoadingManager::LoadingEnd()
{
	LoadingCount--;
	if (LoadingCount == 0)
	{
		// UI 닫기
		if (UUiPopUpManager* PopUpMgr = GetGameInstance()->GetSubsystem<UUiPopUpManager>())
		{
			PopUpMgr->PopPopup();
		}
		UE_LOG(LogTemp, Error, TEXT("LodingEnd()"));
	}
}
