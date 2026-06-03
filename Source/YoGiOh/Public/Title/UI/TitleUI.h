// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "System/Popup/UiPopUpBase.h"
#include "Blueprint/UserWidget.h"
#include "TitleUI.generated.h"

UCLASS()
class YOGIOH_API UTitleUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_AddUser;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_DeckList;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Calculator;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_RollManual;

	UFUNCTION()
	void OnAddUserButtonClicked();
	
	UFUNCTION()
	void OnDeckListButtonClicked();

	UFUNCTION()
	void OnCalculatorButtonClicked();

	UFUNCTION()
	void OnRollManualButtonClicked();

};
