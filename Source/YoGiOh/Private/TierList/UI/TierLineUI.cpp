// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierLineUI.h"
#include "TierList/UI/TierSlotUI.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UTierLineUI::InitializeLine(const FString& InTierName)
{
	Text_TierName->SetText(FText::FromString(InTierName));
}

void UTierLineUI::AddSlot(UTierSlotUI* SlotWidget)
{
	Box_Slots->AddChild(SlotWidget);
}
