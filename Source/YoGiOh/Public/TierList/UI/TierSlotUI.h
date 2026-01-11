// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Deck/Domain/DeckSaveData.h"
#include "TierSlotUI.generated.h"


DECLARE_DELEGATE_OneParam(FOnDeckSlotClicked, const FDeckSaveData&);

class UButton;
class UTextBlock;

UCLASS()
class YOGIOH_API UTierSlotUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;
	
	FOnDeckSlotClicked OnClicked;

	UPROPERTY()
	UButton* Button_Select;

	UPROPERTY()
	UButton* Image_Thumbnail;

	UPROPERTY()
	UTextBlock* Text_DeckName;

	void SetDeckID(FString deckID);
	
private:
	UFUNCTION()
	void HandleClicked();
	FString deckId;
};
