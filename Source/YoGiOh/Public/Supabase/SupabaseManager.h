// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Deck/Type/FDeckTypes.h"
#include "User/Type/FUserTypes.h"
#include "SupabaseManager.generated.h"

UCLASS()
class YOGIOH_API USupabaseManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    
    	void InsertDeck(const FDeckDomain& Domain);
    	void GetDecks();
		void DeleteDeck();
	
		void InsertUser(const FYogUserDomain& Domain);
		void GetUsers();
		void DeleteUser();
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDecksLoaded, const FDeckMap&);
	FOnDecksLoaded OnDecksLoaded;
	DECLARE_MULTICAST_DELEGATE(FOnDecksLoadFailed)
	FOnDecksLoadFailed OnDecksLoadFailed;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUsersLoaded, const FUserMap&);
	FOnUsersLoaded OnUsersLoaded;
	DECLARE_MULTICAST_DELEGATE(FOnUsersLoadFalied)
	FOnUsersLoadFalied OnUsersLoadFailed;
    private:
    
    	FString baseUrl = TEXT("https://glwbfchdscnwtuiovovr.supabase.co");
    
    	FString apiKey = TEXT("sb_publishable_Ns0wUPHBXPDOUo4sXypOZQ_jfQ3Nomk");
    
    	FString table_Decks = TEXT("decks");
	
    	FString table_User = TEXT("user");

};
