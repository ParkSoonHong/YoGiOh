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

void UTierSlotUI::SetData(const FDeckSaveData& Data)
{
 /*
	if (UTexture2D* Tex = LoadThumbnail(InData)) // Manager or Helper 통해
	{
		FButtonStyle Style = Button_Select->WidgetStyle;

		FSlateBrush Brush;
		Brush.SetResourceObject(Tex);
		Brush.ImageSize = FVector2D(256, 256);

		Style.SetNormal(Brush);
		Style.SetHovered(Brush);
		Style.SetPressed(Brush);

		Button_Select->SetStyle(Style);
	}
	*/
	DeckData = Data;
	Text_DeckName->SetText(FText::FromString(Data.DeckName));
}

void UTierSlotUI::HandleClicked()
{
	OnClicked.ExecuteIfBound(DeckData);
}
