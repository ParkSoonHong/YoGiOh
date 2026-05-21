// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Domain/FDeckDomain.h"

/**
 * 
 */
class YOGIOH_API FDeckRepository
{
public:
	 bool Save(const FDeckDomain& Domain);
	 bool LoadAll(TArray<FDeckDomain>& OutDomains);

	FString GetDeckFilePath(const FDeckDomain& Domain) const;
private:
	FString saveDirectory = FPaths::ProjectSavedDir() / TEXT("Decks");
};
