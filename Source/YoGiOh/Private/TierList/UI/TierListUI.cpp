// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierListUI.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Deck/Impoter/DeckImageImporter.h"
#include "System/Popup/Manager/UiPopUpManager.h"
#include "Deck/Manager/DeckManager.h"
#include "Deck/Rules/FDeckRankRules.h"
#include "Deck/Type/EDeckRank.h"
#include "TierList/UI/TierLineUI.h"
#include "TierList/UI/TierSlotUI.h"


void UTierListUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->OnDeckListChanged.AddUObject(this, &UTierListUI::RefreshList);
		RefreshList(deckMgr->GetDecks());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DeckManager Null"));
		return;
	}
// 버튼
	if (Button_DataAdd)
	{
		Button_DataAdd->OnClicked.AddDynamic(this,&UTierListUI::OnClickedDataAddButton);
	}
	if (Button_Back)
	{
		Button_Back->OnClicked.AddDynamic(this,&UTierListUI::OnClickedBackButton);
	}
	if (Button_Search)
	{
		Button_Search->OnClicked.AddDynamic(this,&UTierListUI::OnClickedSearchButton);
	}
// 편집 박스	 
	if (EditableText_InsertText)
	{
		EditableText_InsertText->OnTextCommitted.AddDynamic(this,&UTierListUI::OnInsertTextCommitted);
	}
// 콤보 박스	
	if (ComboBoxString_Filter)
	{
		ComboBoxString_Filter->OnSelectionChanged.AddDynamic(this,&UTierListUI::OnFilterSelected);
	}
}

void UTierListUI::BuildTierMap(const TArray<FDeckDomain>& Decks)
{
	tierMap.Reset();
	for (const FDeckDomain& Deck : Decks)
	{
		const EDeckRank rank = FDeckRankRules::GetRank(Deck.GetTotalScore());
		tierMap.FindOrAdd(rank).Add(Deck);
	}
}
// UI 초기화
void UTierListUI::RefreshList(const TArray<FDeckDomain>& Decks)
{
	VerticalBox_Tier->ClearChildren();
	
	if (Decks.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("DeckManager GetDecks Failed"));
		return;
	}
	
	BuildTierMap(Decks);
	
	for (EDeckRank Tier : FDeckRankRules::GetRankOrder())
	{
		const TArray<FDeckDomain>* TierDecks = tierMap.Find(Tier);
		if (!TierDecks || TierDecks->Num() == 0)
		{
			continue; //  존재하지 않는 티어는 스킵
		}

		UTierLineUI* LineWidget =
			CreateWidget<UTierLineUI>(this, LineClass);
	
		LineWidget->InitializeLine(Tier);
		VerticalBox_Tier->AddChild(LineWidget);

		for (const FDeckDomain& domain : *TierDecks)
		{
			UE_LOG(LogTemp, Warning,TEXT("DeckName=%s ImagePath=[%s]"),
			*domain.GetField(EDeckFieldType::DECKNAME),
			*domain.GetImagePath());
			
			UTierSlotUI* tierSlot = CreateWidget<UTierSlotUI>(this, SlotClass);
	
			tierSlot->SetDeckID(domain.GetDeckId()); 
			tierSlot->Text_DeckName->SetText(FText::FromString(domain.GetField(EDeckFieldType::DECKNAME)));
			
			if (UDeckImageImporter* ImageService = GetGameInstance()->GetSubsystem<UDeckImageImporter>())
			{
				FString DeckFileName = domain.GetImagePath();
				
				if (!DeckFileName.IsEmpty())
				{
					UTexture2D * Thumbnail = ImageService->LoadDeckImage(DeckFileName);
					tierSlot->SetThumbnail(Thumbnail);
				}
				
			}
			LineWidget->AddSlot(tierSlot);
		}
	}
}

void UTierListUI::OnClickedDataAddButton()
{
	if (UUiPopUpManager* popupMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		popupMgr->PushPopup(EUIPopUpType::TIERLISTDETAIL);
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

void UTierListUI::OnClickedSearchButton()
{
	const FText& Text =  EditableText_InsertText->GetText();
	
	if (UDeckManager* deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		// 해당하는 이름이 들어간 덱 찾기
	}
}

void UTierListUI::OnFilterSelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (UDeckManager* deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->ApplyFilter(SelectedItem);
	}
}

void UTierListUI::OnInsertTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (UDeckManager* deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		// 해당하는 이름이 들어간 덱 찾기
	}
}
