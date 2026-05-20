// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Type/EDeckStatType.h"

/**
 * 
 */
class YOGIOH_API FDeckDomain
{
public:
	explicit FDeckDomain(const FDeckData& inData);
	
	explicit FDeckDomain();

	// ----- Get -----
	const FString& GetName() const { return data.deckName; }
	float GetTotalScore() const { return data.totalScore; }
	float GetStatScore(EDeckStatType StatType) const;
	
	// ----- Set -----
	bool SetStatScore(EDeckStatType StatType, float NewScore);
	
	// ----- Command -----
	bool Rename(const FString& NewName, FString& OutError);
	void RecalculateScore();

	// ----- Validation -----
	bool IsValid(FString& OutError) const;

	// ----- Convert -----
	FDeckData ToSaveData() const;

private:
	FDeckData data;
};
