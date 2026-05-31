// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Domain/FDeckDomain.h"

bool FDeckJsonSerializer::TrySerialize(const FDeckDomain& Domain, FString& outJson)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();

	jsonObject->SetStringField(TEXT("ImagePath"), Domain.GetImagePath());
	jsonObject->SetStringField(TEXT("DeckName"), Domain.GetField(EDeckFieldType::DECKNAME));
	jsonObject->SetStringField(TEXT("Owner"),Domain.GetField(EDeckFieldType::OWNER));
	jsonObject->SetStringField(TEXT("Comment"), Domain.GetField(EDeckFieldType::COMMENT));

	//jsonObject->SetStringField(TEXT("Owner"), StaticEnum<EDeckOwner>()->GetNameStringByValue((int64)data.deckOwner));

	// Stats
	jsonObject->SetStringField(TEXT("DeckID"), Domain.GetDeckId());
	jsonObject->SetNumberField(TEXT("Deployment"), Domain.GetStatScore(EDeckStatType::DEPLOYMENT));
	jsonObject->SetNumberField(TEXT("Breakthrough"), Domain.GetStatScore(EDeckStatType::BREAKTHROUGH));
	jsonObject->SetNumberField(TEXT("Retention"), Domain.GetStatScore(EDeckStatType::RETENTION));
	jsonObject->SetNumberField(TEXT("Recovery"),Domain.GetStatScore(EDeckStatType::RECOVERY));
	jsonObject->SetNumberField(TEXT("Control"), Domain.GetStatScore(EDeckStatType::CONTROL));
	jsonObject->SetNumberField(TEXT("Flexibility"), Domain.GetStatScore(EDeckStatType::FLEXIBILITY));
	jsonObject->SetNumberField(TEXT("BasePower"), Domain.GetStatScore(EDeckStatType::BASEPOWER));
	jsonObject->SetNumberField(TEXT("RelativeA"), Domain.GetStatScore(EDeckStatType::RELATIVEA));
	jsonObject->SetNumberField(TEXT("RelativeB"), Domain.GetStatScore(EDeckStatType::RELATIVEB));
	
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&outJson);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);
	return true;
}

bool FDeckJsonSerializer::TryDeserialize(const FString& json, FDeckDomain& Domain)
{
    TSharedPtr<FJsonObject> jsonObject;
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(json);

    if (!FJsonSerializer::Deserialize(reader, jsonObject) || !jsonObject.IsValid())
    {
        return false;
    }

    // 2. 문자열은 TryGet
	FString OutString;
    jsonObject->TryGetStringField(TEXT("DeckName"), OutString);
	Domain.SetField(EDeckFieldType::DECKNAME,OutString);
	jsonObject->TryGetStringField(TEXT("Comment"), OutString);
	Domain.SetField(EDeckFieldType::COMMENT,OutString);
	jsonObject->TryGetStringField(TEXT("Owner"), OutString);
	Domain.SetField(EDeckFieldType::OWNER,OutString);
    jsonObject->TryGetStringField(TEXT("ImagePath"), OutString);
	Domain.SetPath(OutString);
    jsonObject->TryGetStringField(TEXT("DeckID"), OutString);
	Domain.SetDeckId(OutString);


	/*
	FString ownerStr;
	if (jsonObject->TryGetStringField(TEXT("Owner"), ownerStr))
	{
		int64 enumValue = StaticEnum<EDeckOwner>()->GetValueByNameString(ownerStr);
		if (enumValue != INDEX_NONE)
		{
			outData.deckOwner = static_cast<EDeckOwner>(enumValue);
		}
	}
	*/
	
	// json은 내부적으로 double
	// 암묵적으로 float캐스팅
	double value;
	if (jsonObject->TryGetNumberField(TEXT("Deployment"), value))
	{
		Domain.SetStatScore(EDeckStatType::DEPLOYMENT,static_cast<float>(value));
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Breakthrough"), value))
	{
		Domain.SetStatScore(EDeckStatType::BREAKTHROUGH,static_cast<float>(value));
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Retention"), value))
	{
		Domain.SetStatScore(EDeckStatType::RETENTION,static_cast<float>(value));
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Recovery"), value))
	{
		Domain.SetStatScore(EDeckStatType::RECOVERY,static_cast<float>(value));
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Control"), value))
	{
		Domain.SetStatScore(EDeckStatType::CONTROL,static_cast<float>(value));
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Flexibility"), value))
	{
		Domain.SetStatScore(EDeckStatType::FLEXIBILITY,static_cast<float>(value));
	}
	
	if (jsonObject->TryGetNumberField(TEXT("BasePower"), value))
	{
		Domain.SetStatScore(EDeckStatType::BASEPOWER,static_cast<float>(value));
	}
	if (jsonObject->TryGetNumberField(TEXT("RelativeA"), value))
	{
		Domain.SetStatScore(EDeckStatType::RELATIVEA,static_cast<float>(value));
	}
	if (jsonObject->TryGetNumberField(TEXT("RelativeB"), value))
	{
		Domain.SetStatScore(EDeckStatType::RELATIVEB,static_cast<float>(value));
	}
	
    // 4. 배열
   // outData.playablePlayers.Reset();
	/*
    const TArray<TSharedPtr<FJsonValue>>* playerArray;
    if (jsonObject->TryGetArrayField(TEXT("PlayablePlayers"), playerArray))
    {
        for (const TSharedPtr<FJsonValue>& player : *playerArray)
        {
        	FString playerStr;
        	if (player->TryGetString(playerStr))
        	{
        		int64 enumValue = StaticEnum<EPlayablePlayer>()
					->GetValueByNameString(playerStr);

        		if (enumValue != INDEX_NONE)
        		{
        			outData.playablePlayers.Add(
						static_cast<EPlayablePlayer>(enumValue)
					);
        		}
        	}
        }
    }
	*/
    return true;
}
