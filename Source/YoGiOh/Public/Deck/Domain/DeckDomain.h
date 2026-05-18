// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Data/DeckData.h"

/**
 * 
 */
class YOGIOH_API DeckDomain
{
public:
	explicit DeckDomain(const FDeckData& inData);
	
	explicit DeckDomain();

	// ----- Query -----
	const FString& GetName() const { return data.deckName; }
	int32 GetTotalScore() const { return data.totalScore; }

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
