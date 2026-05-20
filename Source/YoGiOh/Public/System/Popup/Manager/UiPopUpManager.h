// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Popup/UIPopUpType.h" 
#include "Deck/Data/FDeckData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UiPopUpManager.generated.h"

/**
 */

class UUiPopUpBase;
class UDeckManager;

UCLASS()
class YOGIOH_API UUiPopUpManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	
	UUiPopUpManager();
	
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;
	
	void BackInput();

	// Popup
	void PushPopup(EUIPopUpType Type);
	void PopPopup();
	
	// ⭐ 추가
	void PushDeckDetailPopup(const FDeckData& Data);


private:
	 UUiPopUpBase* CreatePopup(EUIPopUpType Type);

	UPROPERTY()
	UDeckManager* DeckManager;
	
	UPROPERTY()
	TArray< UUiPopUpBase*> PopupStack;

	UPROPERTY()
	TMap<EUIPopUpType, TSubclassOf<UUiPopUpBase>> PopupClassMap;

	UPROPERTY()
	TMap<EUIPopUpType, UUiPopUpBase*> PopupInstanceMap;
};
