// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Domain/DeckSaveData.h"

/**
 * 
 */
class YOGIOH_API DeckRepository
{
public:
	static bool SaveToJson(const FString& FilePath, const FDeckSaveData& Data);
	static bool LoadFromJson(const FString& FilePath, FDeckSaveData& OutData);
};
