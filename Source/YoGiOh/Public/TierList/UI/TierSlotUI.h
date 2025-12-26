// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common/Base/UiPopUpBase.h"
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
	
	void SetData(const FDeckSaveData& Data);

	FOnDeckSlotClicked OnClicked;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Select;

	UPROPERTY(meta = (BindWidget))
	UButton* Image_Thumbnail;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_DeckName;

private:
	FDeckSaveData DeckData;

	UFUNCTION()
	void HandleClicked();
public:

	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Detail;


};
