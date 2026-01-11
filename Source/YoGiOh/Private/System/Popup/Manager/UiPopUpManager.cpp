// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Popup/Manager/UiPopUpManager.h"
#include "System/Popup/UiPopUpBase.h"
#include "System/Popup/UIPopUpType.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TierList/UI/DeckDetailUI.h"
#include "TierList/UI/TierListUI.h"
#include "Title/UI/TitleUI.h"


UUiPopUpManager::UUiPopUpManager()
{
	/*
	UE_LOG(LogTemp, Warning, TEXT("UiPopUpManager Constructor"));
	
	static ConstructorHelpers::FClassFinder<UTitleUI> 
	TitleUIBP(TEXT("/Game/BluePrints/Ui/WBP_Title"));
	
	if (TitleUIBP.Succeeded())
	{
		PopupClassMap.Add(EUIPopUpType::Title, TitleUIBP.Class);
		UE_LOG(LogTemp, Warning, TEXT("TitleUI BP load OK"));
	}
	
	static ConstructorHelpers::FClassFinder<UTierListUI> 
	TierListUIBP(TEXT("/Game/BluePrints/Ui/WBP_TierList"));
	
	if (TierListUIBP.Succeeded())
	{
		PopupClassMap.Add(EUIPopUpType::TierList, TierListUIBP.Class);
		UE_LOG(LogTemp, Warning, TEXT("TierListUIBP load OK"));
	}
	
	static ConstructorHelpers::FClassFinder<UDeckDetailUI> 
	TierListDetailUIBP(TEXT("/Game/BluePrints/Ui/WBP_CardDetailView"));
	
	if (TierListDetailUIBP.Succeeded())
	{
		PopupClassMap.Add(EUIPopUpType::TierListDetail, TierListDetailUIBP.Class);
		UE_LOG(LogTemp, Warning, TEXT("TierListDetailUIBP load OK"));
	}
	*/
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
}

void UUiPopUpManager::PushPopup(EUIPopUpType Type)
{
	UUiPopUpBase* Popup = CreatePopup(Type);
	if (!Popup)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Create POPUP"));
		return;
	}

	// Pop 요청 바인딩
	Popup->OnRequestPop.AddUObject(this, &UUiPopUpManager::PopPopup);
	Popup->OnRequestPush.AddUObject(this, &UUiPopUpManager::PushPopup);
	
	UE_LOG(LogTemp, Warning, TEXT("AddToViewport POPUP"));
	Popup->AddToViewport();
	PopupStack.Push(Popup);
}

void UUiPopUpManager::PopPopup()
{
	if (PopupStack.Num() == 0)
	{
		return;
	}
	
	UUiPopUpBase* Top = PopupStack.Pop();
	Top->RemoveFromParent();
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

	return CreateWidget<UUiPopUpBase>
	(
		GetWorld(),
		PopupClass
	);
}
