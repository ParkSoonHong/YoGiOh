// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Repository/DeckRepository.h"
#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"


bool FDeckRepository::SaveToJson(const FString& filePath, const FDeckData& data)
{
	FString json;
	if (!FDeckJsonSerializer::TrySerialize(data,json))
	{
		return false;
	}
	return FFileHelper::SaveStringToFile(json, *filePath);
}


bool FDeckRepository::LoadFromJson(const FString& filePath, FDeckData& outData)
{
	outData = FDeckData();
    FString jsonString;
	
	if (!FFileHelper::LoadFileToString(jsonString, *filePath))
	{
		return false;
	}
	return  FDeckJsonSerializer::TryDeserialize(jsonString,outData);
}
