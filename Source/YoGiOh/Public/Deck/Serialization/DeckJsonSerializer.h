// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Data/DeckData.h"

/**
 * 
 */
class YOGIOH_API FDeckJsonSerializer
{

public:
	static  bool TrySerialize(const FDeckData& data, FString& outJson);
	static  bool TryDeserialize(const FString& json, FDeckData& outData);
};
