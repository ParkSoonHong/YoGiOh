// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Calculation/FDeckScoreCalculator.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Type/EDeckFieldType.h"
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
	const FString& GetImagePath() const { return data.imagePath; }
	const FString& GetDeckId() const{ return data.deckID;}
	float GetTotalScore() const { return FDeckScoreCalculator::TotalScoreCalculation(data); }
	
	float GetStatScore(EDeckStatType StatType) const;
	FString GetField(EDeckFieldType FieldType) const;
	//const FDeckData& GetDeckData() const;
	
	// ----- Set -----
	bool SetStatScore(EDeckStatType StatType, float NewScore);
	bool SetField(EDeckFieldType FieldType, const FString& Field);
	bool SetPath(const FString& Path);
	bool SetDeckId();
	void SetDeckId(const FString& DeckId);
	
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
