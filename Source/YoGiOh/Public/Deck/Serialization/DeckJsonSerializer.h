// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Domain/FDeckDomain.h"

/**
 * 
 */
class YOGIOH_API FDeckJsonSerializer
{

public:
	static  bool TrySerialize(const FDeckDomain& Domain, FString& outJson);
	static  bool TryDeserialize(const FString& json, FDeckDomain& Domain);
};
