// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common/Base/UIPopUpType.h"
#include "UiPopUpBase.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UUiPopUpBase : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPopupChangeRequest, EUIPopUpType);
	FOnPopupChangeRequest OnPopupChangeRequest;

	// 현재 화면 종료 (Back / Close)
	DECLARE_MULTICAST_DELEGATE(FOnCloseRequest);
	FOnCloseRequest OnCloseRequest;
};
