// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierListUI.h"
//#include "System/Popup/UiPopUpManager.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "System/Popup/Manager/UiPopUpManager.h"
#include "Deck/Manager/DeckManager.h"
#include "TierList/UI/TierLineUI.h"


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
	
	if (Button_Back)
	{
		Button_Back->OnClicked.AddDynamic(this,&UTierListUI::OnClickedBackButton);
	}
}

void UTierListUI::BuildTierMap(const TArray<FDeckData>& Decks)
{
//	tierMap.Reset();

	for (const FDeckData& Deck : Decks)
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
	TArray<FDeckDomain> Decks = DeckManager->GetDecks();

	if (Decks.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("DeckManager GetDecks Failed"));
		return;
	}
	//BuildTierMap(Decks);
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
void UTierListUI::HandleSlotClicked(const FDeckData& Data)
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
	if (UUiPopUpManager* popupMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		popupMgr->PushPopup(EUIPopUpType::TierListDetail);
	}
	
	if (UDeckManager* deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->CreateDeck();
	}
}

void UTierListUI::OnClickedBackButton()
{
	if (UUiPopUpManager* PopupMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupMgr->PopPopup();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
}
