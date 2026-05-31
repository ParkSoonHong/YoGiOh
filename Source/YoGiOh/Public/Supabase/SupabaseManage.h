// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SupabaseManage.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API USupabaseManage : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	public:
    	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    
    	void InsertDeck(const FDeckDomain& Domain);
    	void GetDecks();
		void DeleteDeck();
	
		void InsertUser();
		void GetUser();
		void DeleteUser();
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDecksLoaded, const TArray<FDeckDomain>&);

	FOnDecksLoaded OnDecksLoaded;
    private:
    
    	FString baseUrl =
    		TEXT("https://glwbfchdscnwtuiovovr.supabase.co");
    
    	FString apiKey =
    		TEXT("sb_publishable_Ns0wUPHBXPDOUo4sXypOZQ_jfQ3Nomk");
    
    	FString table_Decks =
    		TEXT("decks");

};
