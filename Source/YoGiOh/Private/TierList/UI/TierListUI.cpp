// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierListUI.h"
#include "Deck/Domain/DeckSaveData.h"
#include "Common/Manager/UiPopUpManager.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Deck/Manager/DeckManager.h"
#include "TierList/UI/DeckDetailUI.h"
#include "TierList/UI/TierLineUI.h"
#include "TierList/UI/TierSlotUI.h"


void UTierListUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	DeckManager = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>();

	if (DeckManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("DeckManager Null"));
		return;
	}
	
	DeckManager->OnDeckListChanged.AddUObject(this, &UTierListUI::RefreshList);

	if (Button_DataAdd)
	{
		Button_DataAdd->OnClicked.AddDynamic(this,&UTierListUI::OnClickedDataAddButton);
	}
}

void UTierListUI::RefreshList()
{
	TArray<FDeckSaveData> Decks;
	if (!DeckManager->LoadAllDecks(Decks))
	{
		UE_LOG(LogTemp, Warning, TEXT("DeckManager LoadAllDecks Failed"));
		return;
	}

	for (const FDeckSaveData& Data : Decks)
	{
		UTierSlotUI* SlotWidget = CreateWidget<UTierSlotUI>(this, SlotClass);
		SlotWidget->SetData(Data);

		SlotWidget->OnClicked.BindLambda([this](const FDeckSaveData& ClickedData)
		{
			if (UUiPopUpManager* PopupMgr =
				GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
			{
				PopupMgr->PushDeckDetailPopup(ClickedData);
			}
		});

		VerticalBox_Tier->AddChild(SlotWidget);
	}
}
void UTierListUI::HandleSlotClicked(const FDeckSaveData& Data)
{
	if (UUiPopUpManager* PopupMgr =
				GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupMgr->PushPopup(EUIPopUpType::TierListDetail);
	}
}

void UTierListUI::OnClickedDataAddButton()
{
	if (UUiPopUpManager* PopupMgr =
				GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		FDeckSaveData Data;
		PopupMgr->PushDeckDetailPopup(Data);
		UE_LOG(LogTemp,Warning, TEXT("TierListUI ClickedDataAddButton"));
	}
}
