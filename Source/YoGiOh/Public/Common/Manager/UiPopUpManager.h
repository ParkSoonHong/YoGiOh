// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Base/UIPopUpType.h" 
#include "Subsystems/WorldSubsystem.h"
#include "UiPopUpManager.generated.h"

class UUiPopUpBase;

UCLASS()
class YOGIOH_API UUiPopUpManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void BackInput();

	// Screen
	void ShowScreen(EUIPopUpType Type);

	// Popup
	void PushPopup(TSubclassOf<UUiPopUpBase> PopupClass);
	void PopPopup();

private:
	UPROPERTY()
	UUiPopUpBase* CurrentScreen;

	UPROPERTY()
	TArray<UUiPopUpBase*> PopupStack;


};
