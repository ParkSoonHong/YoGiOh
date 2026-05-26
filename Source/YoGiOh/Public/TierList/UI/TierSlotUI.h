// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Deck/Data/FDeckData.h"
#include "TierSlotUI.generated.h"


DECLARE_DELEGATE_OneParam(FOnDeckSlotClicked, const FDeckData&);

class UButton;
class UTextBlock;

UCLASS()
class YOGIOH_API UTierSlotUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Detail;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_DeckName;

	void SetDeckID(FString deckID);
	
	void SetThumbnail(UTexture2D* Thumbnail);
	
private:
	UFUNCTION()
	void OnClickedSelectButton();
	
	FString deckId;
};
