// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common/Base/UiPopUpBase.h"
#include "TierSlotUI.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UTierSlotUI : public UUiPopUpBase
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnDetailButtonClicked();

public:

	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Detail;


};
