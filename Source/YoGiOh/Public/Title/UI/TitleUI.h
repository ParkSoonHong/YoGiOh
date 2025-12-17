// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Base/UiPopUpBase.h"
#include "TitleUI.generated.h"

UCLASS()
class YOGIOH_API UTitleUI : public UUiPopUpBase
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_DeckList;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Calculator;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_RollManual;

	UFUNCTION()
	void OnDeckListButtonClicked();

	UFUNCTION()
	void OnCalculatorButtonClicked();

	UFUNCTION()
	void OnRollManualButtonClicked();

};
