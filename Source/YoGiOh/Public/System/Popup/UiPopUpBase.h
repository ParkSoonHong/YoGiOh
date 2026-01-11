// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "System/Popup/UIPopUpType.h" 
#include "UiPopUpBase.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UUiPopUpBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestPush, EUIPopUpType);
	FOnRequestPush OnRequestPush;

	DECLARE_MULTICAST_DELEGATE(FOnRequestPop);
	FOnRequestPop OnRequestPop;
	
};
