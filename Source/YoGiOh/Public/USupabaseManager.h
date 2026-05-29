// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "USupabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UUSupabaseManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void TestInsertDeck();
	void TestGetDecks();

private:

	FString BaseUrl =
		TEXT("https://glwbfchdscnwtuiovovr.supabase.co");

	FString ApiKey =
		TEXT("sb_publishable_Ns0wUPHBXPDOUo4sXypOZQ_jfQ3Nomk");

	FString TableName =
		TEXT("Testdecks");
};
