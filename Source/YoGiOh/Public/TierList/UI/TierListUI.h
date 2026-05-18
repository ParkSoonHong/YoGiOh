// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Popup/UiPopUpBase.h"
#include "Deck/Data/DeckData.h"
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
	
	UPROPERTY(meta = (BindWidget))
	UButton * Button_Back;
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> SlotClass;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> LineClass;
	
	FDeckData PendingDetailData;

private:
	UDeckManager* DeckManager;	

	void BuildTierMap(const TArray<FDeckData>& Decks);
	void RefreshList();

	void HandleSlotClicked(const FDeckData& Data);
private:
	//TMap<EDeckTier,TArray<FDeckSaveData>> tierMap;
public:
	
	UFUNCTION()
	void OnClickedDataAddButton();
	
	UFUNCTION()
	void OnClickedBackButton();
};
