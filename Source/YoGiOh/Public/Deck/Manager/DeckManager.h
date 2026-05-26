// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Domain/FDeckDomain.h"
#include "Deck/Repository/DeckRepository.h"
#include "Deck/Type/EDeckFieldType.h"
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

	FOnDeckListChanged OnDeckListChanged;
	FOnDeckTotatlScoreUpdate OnDeckTotatlScoreUpdate;
	FOnDeckUpdate OnDeckUpdate;
	FOnDeckInitialize OnDeckInitialize;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	bool SaveDeck();
	bool LoadAllDecks();
	bool DeleteDeck(const FString& DeckID, FString& OutError);
	
	TArray<FDeckDomain> GetDecks() const;
	FDeckDomain  GetCurrentDeck() const;
	
	void UpdateStatCurrentDeck(EDeckStatType StatType,float StatScore);
	
	void UpdateFieldCurrentDeck(EDeckFieldType FieldType,const FString& Field);
	
	void UpdateImagePath(const FString& Path);
	
	void CreateDeck();
	void UpdateDeck(const FString& deckId);
	
	void TestLoad(FDeckDomain Domain);
	
private:
	bool FindDeck(const FString& DeckID, FDeckDomain& OutDomain);
	
	TUniquePtr<DeckManagerHelper> DeckHelper;
	TArray<FDeckDomain> Decks;
	FDeckDomain  currentDeck;
	FDeckRepository repository;
};
