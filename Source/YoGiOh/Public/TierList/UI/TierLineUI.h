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
	
	virtual void NativeConstruct() override;
	//void InitializeLine(EDeckTier tier);

	void AddSlot(UTierSlotUI* tierSlot);
	
	UPROPERTY()
	UTextBlock* Text_TierName;

	UPROPERTY()
	UVerticalBox* Box_Slots;	
};
