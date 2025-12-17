// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/TierSlotUI.h"
#include "Components/Button.h"

void UTierSlotUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Warning, TEXT("UTierSlotUI NativeConstruct"));

	if (Button_Detail)
	{
		Button_Detail->OnClicked.AddDynamic(this, &UTierSlotUI::OnDetailButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Button_Detail is NULL"));
	}
}

void UTierSlotUI::OnDetailButtonClicked()
{	
	OnRequestPush.Broadcast(EUIPopUpType::TierListDetail);
	UE_LOG(LogTemp, Warning, TEXT("BroadCast Detail"));
}
