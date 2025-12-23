// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeckSaveData.h"

/**
 * 
 */
class YOGIOH_API DeckDomain
{
public:
	explicit DeckDomain(const FDeckSaveData& InData);

	// ----- Query -----
	const FString& GetName() const { return Data.DeckName; }
	int32 GetTotalScore() const { return Data.TotalScore; }

	// ----- Command -----
	bool Rename(const FString& NewName, FString& OutError);
	void RecalculateScore();

	// ----- Validation -----
	bool IsValid(FString& OutError) const;

	// ----- Convert -----
	FDeckSaveData ToSaveData() const;

private:
	FDeckSaveData Data;
};
