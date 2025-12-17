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
	UUiPopUpManager();
	
	void BackInput();

	// Popup
	void PushPopup(EUIPopUpType Type);
	void PopPopup();

private:
	UUiPopUpBase* CreatePopup(EUIPopUpType Type);
	
private: 
	
	UPROPERTY()
	TArray<UUiPopUpBase*> PopupStack;

	UPROPERTY()
	TMap<EUIPopUpType, TSubclassOf<UUiPopUpBase>> PopupClassMap;

};
