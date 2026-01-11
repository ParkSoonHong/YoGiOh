// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierListUI.h"
#include "Deck/Domain/DeckSaveData.h"
//#include "System/Popup/UiPopUpManager.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Deck/Manager/DeckManager.h"
#include "Deck/Manager/DeckManagerHelper.h"
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

void UTierListUI::BuildTierMap(const TArray<FDeckSaveData>& Decks)
{
//	tierMap.Reset();

	for (const FDeckSaveData& Deck : Decks)
	{
//		const EDeckTier Tier = DeckManagerHelper::CalculateTier(Deck.TotalScore);
//		tierMap.FindOrAdd(Tier).Add(Deck);
	}
}
// UI 초기화
void UTierListUI::RefreshList()
{
	VerticalBox_Tier->ClearChildren();

	if (!DeckManager->LoadAllDecks())
	{
		UE_LOG(LogTemp, Warning, TEXT("DeckManager LoadAllDecks Failed"));
		return;
	}
	TArray<FDeckSaveData> Decks = DeckManager->GetDecks();

	if (Decks.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("DeckManager GetDecks Failed"));
		return;
	}
	BuildTierMap(Decks);
/*
	// 원하는 티어 순서 명시
	static const EDeckTier TierOrder[] =
	{
		EDeckTier::S,
		EDeckTier::A,
		EDeckTier::B,
		EDeckTier::C,
		EDeckTier::D,
		EDeckTier::E,
		EDeckTier::F
	};

	for (EDeckTier Tier : TierOrder)
	{
		const TArray<FDeckSaveData>* TierDecks = tierMap.Find(Tier);
		if (!TierDecks || TierDecks->Num() == 0)
		{
			continue; //  존재하지 않는 티어는 스킵
		}

		UTierLineUI* LineWidget =
			CreateWidget<UTierLineUI>(this, LineClass);

		LineWidget->InitializeLine(Tier);
		VerticalBox_Tier->AddChild(LineWidget);

		for (const FDeckSaveData& Data : *TierDecks)
		{
			UTierSlotUI* tierSlot =
				CreateWidget<UTierSlotUI>(this, SlotClass);

			tierSlot->SetDeckID(Data.DeckID); // ⭐ ID만 저장
			tierSlot->Text_DeckName->SetText(FText::FromString(Data.DeckName));
			LineWidget->AddSlot(tierSlot);
		}
	}
	*/
}
void UTierListUI::HandleSlotClicked(const FDeckSaveData& Data)
{
	/*
	if (UUiPopUpManager* PopupMgr =
				GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupMgr->PushPopup(EUIPopUpType::TierListDetail);
	}
	*/
}

void UTierListUI::OnClickedDataAddButton()
{
	/*
	if (UUiPopUpManager* PopupMgr =
				GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		FDeckSaveData Data;
		PopupMgr->PushDeckDetailPopup(Data);
		UE_LOG(LogTemp,Warning, TEXT("TierListUI ClickedDataAddButton"));
	}
	*/
}
