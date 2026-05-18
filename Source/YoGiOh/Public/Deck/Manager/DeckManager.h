// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Deck/Data/DeckData.h"
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
	bool CreateAndSaveDeck(const FDeckData& InputData, FString& OutError);
	bool SaveDeck(FString& OutError, const FDeckData& Data);
	bool LoadDeck(const FString& FilePath, FDeckData& OutData);
	
	FString GetDeckDir() const;
	
	FString GetDeckFilePath(const FString& DeckID) const;
	
	bool LoadAllDecks();
         
	bool DeleteDeck(const FString& DeckID, FString& OutError);
	
	void NotifyDeckListChanged();
	
	TArray<FDeckData> GetDecks ();
	
	DECLARE_MULTICAST_DELEGATE(FOnDeckListChanged);

	FOnDeckListChanged OnDeckListChanged;
	
private:
	TUniquePtr<DeckManagerHelper> DeckHelper;
	TArray<FDeckData> Decks;
};
