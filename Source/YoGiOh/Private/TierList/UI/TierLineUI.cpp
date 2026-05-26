// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierLineUI.h"

//#include "Common/Base/EDeckTier.h"
#include "TierList/UI/TierSlotUI.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Deck/Rules/FDeckRankRules.h"
#include "Deck/Type/EDeckRank.h"

void UTierLineUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTierLineUI::InitializeLine(EDeckRank Rank)
{
	TierName->SetText(FText::FromString(FDeckRankRules::GetRankText(Rank)));
}

void UTierLineUI::AddSlot(UTierSlotUI* tierSlot)
{
	WrapBox_List->AddChild(tierSlot);
}
