// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TierLineUI.generated.h"

class UVerticalBox;
class UTextBlock;
class UTierSlotUI;
UCLASS()
class YOGIOH_API UTierLineUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitializeLine(const FString& InTierName);

	void AddSlot(UTierSlotUI* SlotWidget);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_TierName;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* Box_Slots;	
};
