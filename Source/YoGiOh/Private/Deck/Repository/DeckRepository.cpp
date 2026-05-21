// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Repository/DeckRepository.h"
#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"


bool FDeckRepository::Save(const FDeckDomain& Domain)
{
	FString json;
	if (!FDeckJsonSerializer::TrySerialize(Domain,json))
	{
		return false;
	}
	return FFileHelper::SaveStringToFile(json, *saveDirectory);
}


bool FDeckRepository::LoadAll(TArray<FDeckData>& OutDomains)
{
	//outData = FDeckData();
    FString jsonString;
	
	if (!FFileHelper::LoadFileToString(jsonString, *saveDirectory))
	{
		return false;
	}
	//return  FDeckJsonSerializer::TryDeserialize(jsonString,outData);
	return  true;
}
