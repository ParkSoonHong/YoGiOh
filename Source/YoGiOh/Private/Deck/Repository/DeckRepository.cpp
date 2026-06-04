// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Repository/DeckRepository.h"
#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Supabase/SupabaseManager.h"


bool FDeckRepository::LocalSave(const FDeckDomain& Domain)
{
	FString json;
	if (!FDeckJsonSerializer::TrySerialize(Domain,json))
	{
		return false;
	}
	
	IFileManager::Get().MakeDirectory(*saveDirectory, true);
	
	FString filePath = saveDirectory / Domain.GetDeckId() + TEXT(".json");
	
	return FFileHelper::SaveStringToFile(json, *filePath);
}


bool FDeckRepository::LocalLoadAll(TMap<FString, FDeckDomain>& OutDeckMap)
{
	OutDeckMap.Reset();
	
	TArray<FString> JsonFiles;

	IFileManager::Get().FindFiles(
		JsonFiles,
		*(saveDirectory / TEXT("*.json")),
		true,
		false);

	if (JsonFiles.IsEmpty())
	{
		UE_LOG(LogTemp,Error,TEXT("Could not load JsonFiles "));
		return false;
	}
	
	for (const FString& FileName : JsonFiles)
	{
		FString FilePath = saveDirectory / FileName;

		FString JsonString;

		if (!FFileHelper::LoadFileToString(JsonString,*FilePath))
		{
			UE_LOG(LogTemp,Error,TEXT("Could not load Deck %s"),*FilePath);
			continue;
		}

		FDeckDomain Domain;

		if (!FDeckJsonSerializer::TryDeserialize(JsonString, Domain))
		{
			UE_LOG(LogTemp, Error, TEXT("Deserialize Failed %s"), *FilePath);
			continue;
		}

		const FString DeckId = Domain.GetDeckId();

		if (DeckId.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("DeckId Empty %s"), *FilePath);
			continue;
		}

		OutDeckMap.Add(DeckId, Domain);
	}

	return true;
}

FString FDeckRepository::GetDeckFilePath(const FDeckDomain& Domain) const
{
	FString filePath = saveDirectory / Domain.GetDeckId() + TEXT(".json");
	
	return filePath;
}
