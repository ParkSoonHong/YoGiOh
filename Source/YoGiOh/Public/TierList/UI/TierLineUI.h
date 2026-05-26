// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "Deck/Type/EDeckRank.h"
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
	void InitializeLine(EDeckRank Rank);

	void AddSlot(UTierSlotUI* tierSlot);
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TierName;

	UPROPERTY(meta=(BindWidget))
	UWrapBox* WrapBox_List;	
};
