// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Deck/Domain/FDeckDomain.h"
#include "Deck/Type/EDeckStatType.h"

bool FDeckJsonSerializer::TrySerialize(const FDeckDomain& Domain, FString& outJson)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();
	
	jsonObject->SetStringField(TEXT("deck_id"), Domain.GetDeckId());

	jsonObject->SetStringField(TEXT("deck_name"), Domain.GetField(EDeckFieldType::DECKNAME));
	jsonObject->SetStringField(TEXT("owner_id"),Domain.GetField(EDeckFieldType::OWNERID));
	jsonObject->SetStringField(TEXT("comment"), Domain.GetField(EDeckFieldType::COMMENT));
	jsonObject->SetStringField(TEXT("image_path"), Domain.GetImagePath());

	// Stats
	jsonObject->SetNumberField(TEXT("deployment"), Domain.GetStatScore(EDeckStatType::DEPLOYMENT));
	jsonObject->SetNumberField(TEXT("breakthrough"), Domain.GetStatScore(EDeckStatType::BREAKTHROUGH));
	jsonObject->SetNumberField(TEXT("retention"), Domain.GetStatScore(EDeckStatType::RETENTION));
	jsonObject->SetNumberField(TEXT("recovery"),Domain.GetStatScore(EDeckStatType::RECOVERY));
	jsonObject->SetNumberField(TEXT("control"), Domain.GetStatScore(EDeckStatType::CONTROL));
	jsonObject->SetNumberField(TEXT("flexibility"), Domain.GetStatScore(EDeckStatType::FLEXIBILITY));
	jsonObject->SetNumberField(TEXT("base_power"), Domain.GetStatScore(EDeckStatType::BASEPOWER));
	jsonObject->SetNumberField(TEXT("relative_a"), Domain.GetStatScore(EDeckStatType::RELATIVEA));
	jsonObject->SetNumberField(TEXT("relative_b"), Domain.GetStatScore(EDeckStatType::RELATIVEB));
	
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&outJson);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);
	return true;
}

bool FDeckJsonSerializer::TryDeserialize(const FString& Json, FDeckDomain& Domain)
{
    TSharedPtr<FJsonObject> jsonObject;
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Json);

	if (!FJsonSerializer::Deserialize(reader, jsonObject) || !jsonObject.IsValid())
	{
		return false;
	}

	return TryDeserializeObject(jsonObject, Domain);
}

bool FDeckJsonSerializer::TryDeserializeArray(const FString& Json, FDeckMap& OutDecks)
{
	OutDecks.Reset();

	TArray<TSharedPtr<FJsonValue>> jsonArray;

	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Json);

	if (!FJsonSerializer::Deserialize(reader, jsonArray))
	{
		return false;
	}

	for (const TSharedPtr<FJsonValue>& value : jsonArray)
	{
		if (!value.IsValid())
		{
			continue;
		}

		TSharedPtr<FJsonObject> jsonObject = value->AsObject();

		if (!jsonObject.IsValid())
		{
			continue;
		}

		FDeckDomain domain;

		if (!TryDeserializeObject(jsonObject, domain))
		{
			continue;
		}

		const FString deckId = domain.GetDeckId();

		if (deckId.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("DeckId is empty"));
			continue;
		}

		OutDecks.Add(deckId, domain);
	}

	return true;
}

bool FDeckJsonSerializer::TryDeserializeObject(const TSharedPtr<FJsonObject>& JsonObject, FDeckDomain& Domain)
{
	if (!JsonObject.IsValid())
	{
		return false;
	}
	FString OutString;
	JsonObject->TryGetStringField(TEXT("deck_id"), OutString);
	Domain.SetDeckId(OutString);
	JsonObject->TryGetStringField(TEXT("deck_name"), OutString);
	Domain.SetField(EDeckFieldType::DECKNAME,OutString);
	JsonObject->TryGetStringField(TEXT("owner_id"), OutString);
	Domain.SetField(EDeckFieldType::OWNERID,OutString);
	JsonObject->TryGetStringField(TEXT("comment"), OutString);
	Domain.SetField(EDeckFieldType::COMMENT,OutString);
	JsonObject->TryGetStringField(TEXT("image_path"), OutString);
	Domain.SetPath(OutString);
   

	double value;
	if (JsonObject->TryGetNumberField(TEXT("deployment"), value))
	{
		Domain.SetStatScore(EDeckStatType::DEPLOYMENT,static_cast<float>(value));
	}
	
	if (JsonObject->TryGetNumberField(TEXT("breakthrough"), value))
	{
		Domain.SetStatScore(EDeckStatType::BREAKTHROUGH,static_cast<float>(value));
	}
	
	if (JsonObject->TryGetNumberField(TEXT("retention"), value))
	{
		Domain.SetStatScore(EDeckStatType::RETENTION,static_cast<float>(value));
	}
	
	if (JsonObject->TryGetNumberField(TEXT("recovery"), value))
	{
		Domain.SetStatScore(EDeckStatType::RECOVERY,static_cast<float>(value));
	}
	
	if (JsonObject->TryGetNumberField(TEXT("control"), value))
	{
		Domain.SetStatScore(EDeckStatType::CONTROL,static_cast<float>(value));
	}
	
	if (JsonObject->TryGetNumberField(TEXT("flexibility"), value))
	{
		Domain.SetStatScore(EDeckStatType::FLEXIBILITY,static_cast<float>(value));
	}
	
	if (JsonObject->TryGetNumberField(TEXT("base_power"), value))
	{
		Domain.SetStatScore(EDeckStatType::BASEPOWER,static_cast<float>(value));
	}
	if (JsonObject->TryGetNumberField(TEXT("relative_a"), value))
	{
		Domain.SetStatScore(EDeckStatType::RELATIVEA,static_cast<float>(value));
	}
	if (JsonObject->TryGetNumberField(TEXT("relative_b"), value))
	{
		Domain.SetStatScore(EDeckStatType::RELATIVEB,static_cast<float>(value));
	}
	
	return true;
}
