// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeckAddUI.generated.h"


class UButton;

UCLASS()
class YOGIOH_API UDeckAddUI : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_SaveButton;
	
	
	UFUNCTION()
	void OnClickedAddDataButton();
	
};
