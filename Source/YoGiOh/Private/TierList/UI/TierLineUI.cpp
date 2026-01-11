// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierLineUI.h"

//#include "Common/Base/EDeckTier.h"
#include "TierList/UI/TierSlotUI.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UTierLineUI::NativeConstruct()
{
	Super::NativeConstruct();
}
/*
//티어 생성
void UTierLineUI::InitializeLine(EDeckTier tier)
{
	switch (tier)
	{
	case EDeckTier::S: return Text_TierName->SetText(FText::FromString("S"));
	case EDeckTier::A: return Text_TierName->SetText(FText::FromString("A"));
	case EDeckTier::B: return Text_TierName->SetText(FText::FromString("B"));
	case EDeckTier::C: return Text_TierName->SetText(FText::FromString("C"));
	case EDeckTier::D: return Text_TierName->SetText(FText::FromString("D"));
	case EDeckTier::E: return Text_TierName->SetText(FText::FromString("E"));;
	case EDeckTier::F: return Text_TierName->SetText(FText::FromString("F"));;
	}
}
*/
void UTierLineUI::AddSlot(UTierSlotUI* tierSlot)
{
	Box_Slots->AddChild(tierSlot);
}
