// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Base/UiPopUpBase.h"
#include "Deck/Domain/DeckSaveData.h"
#include "TierListUI.generated.h"

class UDeckManager;
class UTierSlotUI;
class UTierLineUI;
class UDeckSlotUI;
class UVerticalBox;
class UButton;
UCLASS()
class YOGIOH_API UTierListUI : public UUiPopUpBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox * VerticalBox_Tier;
	
	UPROPERTY(meta = (BindWidget))
	UButton * Button_DataAdd;
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> SlotClass;
	
	FDeckSaveData PendingDetailData;

private:
	UDeckManager* DeckManager;

	void RefreshList();

	void HandleSlotClicked(const FDeckSaveData& Data);
public:
	
	UFUNCTION()
	void OnClickedDataAddButton();
};
