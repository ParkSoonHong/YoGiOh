// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Type/FDeckTypes.h"

/**
 * 
 */
class YOGIOH_API FDeckJsonSerializer
{

public:
	static  bool TrySerialize(const FDeckDomain& Domain, FString& outJson);
	static  bool TryDeserialize(const FString& Json, FDeckDomain& Domain);
	static bool TryDeserializeArray(const FString& Json,FDeckMap& OutDecks);
private:
	static bool TryDeserializeObject(const TSharedPtr<FJsonObject>& JsonObject,FDeckDomain& Domain);
};
