// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierSlotUI.h"
#include "Components/Button.h"
#include "Deck/Manager/DeckManager.h"

void UTierSlotUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Warning, TEXT("UTierSlotUI NativeConstruct"));
	
	if (Button_Detail)
	{
		Button_Detail->OnClicked.AddDynamic(this, &UTierSlotUI::OnClickedSelectButton);
	}
}


void UTierSlotUI::SetDeckID(FString deckID)
{
	deckId = deckID;
}

void UTierSlotUI::SetThumbnail(UTexture2D* Thumbnail)
{
	FButtonStyle btrStyle = Button_Detail->GetStyle();
	btrStyle.Normal.SetResourceObject(Thumbnail);
	btrStyle.Hovered.SetResourceObject(Thumbnail);
	btrStyle.Pressed.SetResourceObject(Thumbnail);
}

void UTierSlotUI::OnClickedSelectButton()
{
	if (UDeckManager* deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->UpdateDeck(deckId);
	}
}
