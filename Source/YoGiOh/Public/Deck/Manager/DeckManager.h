// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Deck/Domain/DeckSaveData.h"
#include "DeckManager.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UDeckManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	bool CreateAndSaveDeck(const FDeckSaveData& InputData, FString& OutError);
	bool LoadDeck(const FString& FilePath, FDeckSaveData& OutData);
public:
	bool SaveDeck( FString& FilePath, const FDeckSaveData& InData);
	
	FString GetSaveFilePath() const;
};
