// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Popup/Manager/UiPopUpManager.h"
#include "System/Popup/UiPopUpBase.h"
#include "System/Popup/Type/UIPopUpType.h" 

#include "TierList/UI/DeckDetailUI.h"
#include "TierList/UI/TierListUI.h"

#include "System/Loading/Ui/LoadingUi.h"
#include "System/SystemPopup/UI/SystemPopupUI.h"

UUiPopUpManager::UUiPopUpManager()
{
	static ConstructorHelpers::FClassFinder<UTierListUI> 
	TierListUIBP(TEXT("/Game/BluePrints/Ui/WBP_TierList"));
	
	if (TierListUIBP.Succeeded())
	{
		PopupClassMap.Add(EUIPopUpType::TIERLIST, TierListUIBP.Class);
		UE_LOG(LogTemp, Warning, TEXT("WBP_TierList load OK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WBP_TierList Null"));
	}
	
	static ConstructorHelpers::FClassFinder<UDeckDetailUI> 
	TierListDetailUIBP(TEXT("/Game/BluePrints/Ui/WBP_CardDetailView"));
	
	if (TierListDetailUIBP.Succeeded())
	{
		PopupClassMap.Add(EUIPopUpType::TIERLISTDETAIL, TierListDetailUIBP.Class);
		UE_LOG(LogTemp, Warning, TEXT("WBP_CardDetailView load OK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WBP_CardDetailView Null"));
	}
	
	static ConstructorHelpers::FClassFinder<ULoadingUi> 
	LoadingUIBP(TEXT("/Game/BluePrints/Ui/WBP_Loading"));
	
	if (LoadingUIBP.Succeeded())
	{
		PopupClassMap.Add(EUIPopUpType::LODING, LoadingUIBP.Class);
		UE_LOG(LogTemp, Warning, TEXT("WBP_Loading load OK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WBP_Loading Null"));
	}
	
	static ConstructorHelpers::FClassFinder<USystemPopupUI> 
	SystemPopupUIBP(TEXT("/Game/BluePrints/Ui/WBP_SystemPopup"));
	
	if (SystemPopupUIBP.Succeeded())
	{
		PopupClassMap.Add(EUIPopUpType::SYSTEM, SystemPopupUIBP.Class);
		UE_LOG(LogTemp, Warning, TEXT("WBP_SystemPopup load OK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WBP_SystemPopup Null"));
	}
	
}

void UUiPopUpManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

void UUiPopUpManager::Deinitialize()
{
	Super::Deinitialize();
}

void UUiPopUpManager::BackInput()
{
	if (PopupStack.Num() > 1)
	{
		PopPopup();
		return;
	}
	/*
	else if (PopupStack.Num() == 0)
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			UKismetSystemLibrary::QuitGame
			(
				GetWorld(),
				PC,
				EQuitPreference::Quit,
				false
			);
		}
	}
	*/
}

void UUiPopUpManager::PushPopup(EUIPopUpType Type)
{
	UUiPopUpBase* Popup = CreatePopup(Type);
	
	if (!Popup)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Create POPUP"));
		return;
	}
	
	// 혹시모를 중복 push 방지 
	if (PopupStack.Contains(Popup))
	{
		return;
	}
	
	Popup->SetVisibility(ESlateVisibility::Visible);
	PopupStack.Push(Popup);
}

void UUiPopUpManager::PopPopup()
{
	if (PopupStack.Num() == 0)
	{
		return;
	}
	
	UUiPopUpBase* Top = PopupStack.Pop();
	Top->SetVisibility(ESlateVisibility::Collapsed);
}

UUiPopUpBase* UUiPopUpManager::CreatePopup(EUIPopUpType Type)
{
	// 이미 생성되어있으면 반환
	if (PopupInstanceMap.Contains(Type))
	{
		UE_LOG(LogTemp,Verbose, TEXT("Popup already exists"));
		return PopupInstanceMap[Type];
	}
	
	if (!PopupClassMap.Contains(Type))
	{
		UE_LOG(LogTemp, Error, TEXT("Popup class not registered"));
		return nullptr;
	}

	TSubclassOf<UUiPopUpBase> PopupClass = PopupClassMap[Type];
	
	if (!PopupClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Popup class nullptr"));
		return nullptr;
	}
	
	UUiPopUpBase* NewPopup = CreateWidget<UUiPopUpBase>(GetWorld(), PopupClass);

	if (!NewPopup)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Create Popup"));
		return nullptr;
	}
	
	NewPopup->AddToViewport();
	NewPopup->SetVisibility(ESlateVisibility::Collapsed);
	
	PopupInstanceMap.Add(Type, NewPopup);
	
	return NewPopup;
}
