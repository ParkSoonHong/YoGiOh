// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Data/FDeckData.h"

/**
 * 
 */
class YOGIOH_API FDeckRepository
{
public:
	static bool SaveToJson(const FString& filePath, const FDeckData& data);
	static bool LoadFromJson(const FString& filePath, FDeckData& outData);
};
