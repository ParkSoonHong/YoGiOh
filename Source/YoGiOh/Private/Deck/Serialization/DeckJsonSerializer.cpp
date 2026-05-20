// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Deck/Data/FDeckData.h"

bool FDeckJsonSerializer::TrySerialize(const FDeckData& data, FString& outJson)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();

	jsonObject->SetStringField(TEXT("DeckName"), data.deckName);
	jsonObject->SetStringField(TEXT("ImagePath"), data.imagePath);
	jsonObject->SetStringField(TEXT("Owner"),data.deckOwner);
	//jsonObject->SetStringField(TEXT("Owner"), StaticEnum<EDeckOwner>()->GetNameStringByValue((int64)data.deckOwner));

	// Stats
	jsonObject->SetStringField(TEXT("DeckID"), data.deckID);
	jsonObject->SetNumberField(TEXT("Deployment"), data.deployment);
	jsonObject->SetNumberField(TEXT("Breakthrough"), data.breakthrough);
	jsonObject->SetNumberField(TEXT("Retention"), data.retention);
	jsonObject->SetNumberField(TEXT("Recovery"), data.recovery);
	jsonObject->SetNumberField(TEXT("Control"), data.control);
	jsonObject->SetNumberField(TEXT("Flexibility"), data.flexibility);
	jsonObject->SetNumberField(TEXT("BasePower"), data.basePower);
	jsonObject->SetNumberField(TEXT("RelativeA"), data.relativeA);
	jsonObject->SetNumberField(TEXT("RelativeB"), data.relativeB);
	jsonObject->SetNumberField(TEXT("TotalScore"), data.totalScore);

	jsonObject->SetStringField(TEXT("Comment"), data.comment);

	// PlayablePlayers
	TArray<TSharedPtr<FJsonValue>> playerArray;
	for (EPlayablePlayer player : data.playablePlayers)
	{
		playerArray.Add(MakeShared<FJsonValueString>(
			StaticEnum<EPlayablePlayer>()->GetNameStringByValue((int64)player)
		));
	}
	jsonObject->SetArrayField(TEXT("PlayablePlayers"), playerArray);

	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&outJson);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);
	return true;
}

bool FDeckJsonSerializer::TryDeserialize(const FString& json, FDeckData& outData)
{
    TSharedPtr<FJsonObject> jsonObject;
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(json);

    if (!FJsonSerializer::Deserialize(reader, jsonObject) || !jsonObject.IsValid())
    {
        return false;
    }

    // 2. 문자열은 TryGet
    jsonObject->TryGetStringField(TEXT("DeckName"), outData.deckName);
    jsonObject->TryGetStringField(TEXT("ImagePath"), outData.imagePath);
    jsonObject->TryGetStringField(TEXT("DeckID"), outData.deckID);
    jsonObject->TryGetStringField(TEXT("Comment"), outData.comment);
    jsonObject->TryGetStringField(TEXT("Owner"), outData.deckOwner);

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
		outData.deployment = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Breakthrough"), value))
	{
		outData.breakthrough = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Retention"), value))
	{
		outData.retention = static_cast<float>(value);

	}
	
	if (jsonObject->TryGetNumberField(TEXT("Recovery"), value))
	{
		outData.recovery = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Control"), value))
	{
		outData.control = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Flexibility"), value))
	{
		outData.flexibility = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("BasePower"), value))
	{
		outData.basePower = static_cast<float>(value);
	}
	if (jsonObject->TryGetNumberField(TEXT("RelativeA"), value))
	{
		outData.relativeA = static_cast<float>(value);
	}
	if (jsonObject->TryGetNumberField(TEXT("RelativeB"), value))
	{
		outData.relativeB = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("TotalScore"), value))
	{
		outData.totalScore = static_cast<float>(value);
	}

    // 4. 배열
    outData.playablePlayers.Reset();

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

    return true;
}
