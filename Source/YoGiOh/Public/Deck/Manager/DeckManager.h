// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Deck/Repository/DeckRepository.h"
#include "Deck/Type/EDeckFieldType.h"
#include "Deck/Type/FDeckTypes.h"
#include "DeckManager.generated.h"

class DeckManagerHelper;
/**
 * 
 */
UCLASS()
class YOGIOH_API UDeckManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE(FOnDeckListChanged);
	DECLARE_MULTICAST_DELEGATE(FOnDeckTotatlScoreUpdate);
	DECLARE_MULTICAST_DELEGATE(FOnDeckUpdate);
	DECLARE_MULTICAST_DELEGATE(FOnDeckInitialize);
	DECLARE_MULTICAST_DELEGATE(FOnDeckLoadcompleted);

	FOnDeckListChanged OnDeckListChanged;
	FOnDeckTotatlScoreUpdate OnDeckTotatlScoreUpdate;
	FOnDeckUpdate OnDeckUpdate;
	FOnDeckInitialize OnDeckInitialize;
	FOnDeckLoadcompleted OnDeckLoadcompleted;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void LoadingStart();
	
	bool LocalSaveDeck();
	bool LocalSaveAllDeck();
	bool LocalLoadAllDecks();
	
	bool ServerLoadAllDeck();
	bool ServerSaveDeck();
	
	bool DeleteDeck(const FString& DeckID, FString& OutError);
	
	void LoadingCompleted(const FDeckMap& DeckMap);
	void LoadingFailed();
	
	TArray<FDeckDomain> GetDecks() const;
	FDeckDomain  GetCurrentDeck() const { return currentDeck; };
	
	void UpdateStatCurrentDeck(EDeckStatType StatType,float StatScore);
	
	void UpdateFieldCurrentDeck(EDeckFieldType FieldType,const FString& Field);
	
	void UpdateImagePath(const FString& Path);
	
	void CreateDeck();
	void UpdateDeck(const FString& DeckId);

private:
	bool FindDeck(const FString& DeckID, FDeckDomain& OutDomain);
	
	FDeckMap deckMap;
	FDeckDomain  currentDeck;
	FDeckRepository repository;
};
