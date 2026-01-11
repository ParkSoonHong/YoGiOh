// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierSlotUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Deck/Manager/DeckManagerHelper.h"

void UTierSlotUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Warning, TEXT("UTierSlotUI NativeConstruct"));
	
	if (Button_Select)
	{
		Button_Select->OnClicked.AddDynamic(this, &UTierSlotUI::HandleClicked);
	}
}


void UTierSlotUI::SetDeckID(FString deckID)
{
	deckId = deckID;
}

void UTierSlotUI::HandleClicked()
{
	//OnClicked.ExecuteIfBound(DeckData);
}
