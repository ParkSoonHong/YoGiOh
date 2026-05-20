// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Domain/FDeckDomain.h"
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
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	bool CreateAndSaveDeck(const FDeckData& InputData, FString& OutError);
	bool SaveDeck(FString& OutError, const FDeckData& Data);
	bool LoadDeck(const FString& FilePath, FDeckData& OutData);
	
	FString GetDeckDir() const;
	
	FString GetDeckFilePath(const FString& DeckID) const;
	
	bool LoadAllDecks();
         
	bool DeleteDeck(const FString& DeckID, FString& OutError);
	
	
	TArray<FDeckDomain> GetDecks ();
	
	DECLARE_MULTICAST_DELEGATE(FOnDeckListChanged);
	DECLARE_MULTICAST_DELEGATE(FOndeckUpdate);

	FOndeckUpdate OnDeckUpdate;
	FOnDeckListChanged OnDeckListChanged;
	
	FDeckDomain  GetCurrentDeck() const;
	
	float GetcurrentDeckTotalScore() const;
	
	void CreateDeck();
	
	void UpdateStatCurrentDeck(EDeckStatType StatType,float StatScore);
	
	void UpdateTextCurrentDeck(EDeckFieldType FieldType,const FString& Text);
	
	void EditDeck(const FString& deckId);
	
private:
	void NotifyDeckListChanged();
	TUniquePtr<DeckManagerHelper> DeckHelper;
	TArray<FDeckDomain> Decks;
	FDeckDomain  currentDeck;
};
