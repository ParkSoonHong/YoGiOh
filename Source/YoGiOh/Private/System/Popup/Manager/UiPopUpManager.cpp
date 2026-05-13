// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Popup/Manager/UiPopUpManager.h"
#include "System/Popup/UiPopUpBase.h"
#include "System/Popup/UIPopUpType.h"

#include "Deck/Manager/DeckManager.h"

#include "TierList/UI/DeckDetailUI.h"
#include "TierList/UI/TierListUI.h"

#include "Kismet/KismetSystemLibrary.h"

UUiPopUpManager::UUiPopUpManager()
{
	static ConstructorHelpers::FClassFinder<UTierListUI> 
	TierListUIBP(TEXT("/Game/BluePrints/Ui/WBP_TierList"));
	
	if (TierListUIBP.Succeeded())
	{
		PopupClassMap.Add(EUIPopUpType::TierList, TierListUIBP.Class);
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
		PopupClassMap.Add(EUIPopUpType::TierListDetail, TierListDetailUIBP.Class);
		UE_LOG(LogTemp, Warning, TEXT("WBP_TierListDetail load OK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WBP_TierListDetail Null"));
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

void UUiPopUpManager::PushDeckDetailPopup(const FDeckSaveData& Data)
{
	//PushPopup(EUIPopUpType::TierListDetail);

	UUiPopUpBase* Top = PopupStack.Last();
	if (UDeckDetailUI* Detail = Cast<UDeckDetailUI>(Top))
	{
		if (!DeckManager)
		{
			DeckManager = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>();
		}

		Detail->InitializeDetail(DeckManager, Data);
	}
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
	
	// 옵저버 패턴 요청 등록 
	NewPopup->OnRequestPop.AddUObject(this, &UUiPopUpManager::PopPopup);
	NewPopup->OnRequestPush.AddUObject(this, &UUiPopUpManager::PushPopup);
	
	PopupInstanceMap.Add(Type, NewPopup);
	
	return NewPopup;
}
