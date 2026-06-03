// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Popup/UiPopUpBase.h"
#include "UserProfileUI.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UUserProfileUI : public UUiPopUpBase
{
	GENERATED_BODY()
	
	virtual  void NativeConstruct() override;
	
};
