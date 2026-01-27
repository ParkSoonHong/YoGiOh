// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Deck/Data/DeckData.h"

bool FDeckJsonSerializer::TrySerialize(const FDeckData& data, FString& outJson)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();

	jsonObject->SetStringField(TEXT("DeckName"), data.DeckName);
	jsonObject->SetStringField(TEXT("ImagePath"), data.ImagePath);
	jsonObject->SetStringField(TEXT("Owner"),
	StaticEnum<EDeckOwner>()->GetNameStringByValue((int64)data.DeckOwner));

	// Stats
	jsonObject->SetStringField(TEXT("DeckID"), data.DeckID);
	jsonObject->SetNumberField(TEXT("Deployment"), data.Deployment);
	jsonObject->SetNumberField(TEXT("Breakthrough"), data.Breakthrough);
	jsonObject->SetNumberField(TEXT("Retention"), data.Retention);
	jsonObject->SetNumberField(TEXT("Recovery"), data.Recovery);
	jsonObject->SetNumberField(TEXT("Control"), data.Control);
	jsonObject->SetNumberField(TEXT("Flexibility"), data.Flexibility);
	jsonObject->SetNumberField(TEXT("BasePower"), data.BasePower);
	jsonObject->SetNumberField(TEXT("RelativeA"), data.RelativeA);
	jsonObject->SetNumberField(TEXT("RelativeB"), data.RelativeB);
	jsonObject->SetNumberField(TEXT("TotalScore"), data.TotalScore);

	jsonObject->SetStringField(TEXT("Comment"), data.Comment);

	// PlayablePlayers
	TArray<TSharedPtr<FJsonValue>> playerArray;
	for (EPlayablePlayer player : data.PlayablePlayers)
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
    jsonObject->TryGetStringField(TEXT("DeckName"), outData.DeckName);
    jsonObject->TryGetStringField(TEXT("ImagePath"), outData.ImagePath);
    jsonObject->TryGetStringField(TEXT("DeckID"), outData.DeckID);
    jsonObject->TryGetStringField(TEXT("Comment"), outData.Comment);

	FString ownerStr;
	if (jsonObject->TryGetStringField(TEXT("Owner"), ownerStr))
	{
		int64 enumValue = StaticEnum<EDeckOwner>()->GetValueByNameString(ownerStr);
		if (enumValue != INDEX_NONE)
		{
			outData.DeckOwner = static_cast<EDeckOwner>(enumValue);
		}
	}
	
	// json은 내부적으로 double
	// 암묵적으로 float캐스팅
	double value;
	if (jsonObject->TryGetNumberField(TEXT("Deployment"), value))
	{
		outData.Deployment = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Breakthrough"), value))
	{
		outData.Breakthrough = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Retention"), value))
	{
		outData.Retention = static_cast<float>(value);

	}
	
	if (jsonObject->TryGetNumberField(TEXT("Recovery"), value))
	{
		outData.Recovery = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Control"), value))
	{
		outData.Control = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("Flexibility"), value))
	{
		outData.Flexibility = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("BasePower"), value))
	{
		outData.BasePower = static_cast<float>(value);
	}
	if (jsonObject->TryGetNumberField(TEXT("RelativeA"), value))
	{
		outData.RelativeA = static_cast<float>(value);
	}
	if (jsonObject->TryGetNumberField(TEXT("RelativeB"), value))
	{
		outData.RelativeB = static_cast<float>(value);
	}
	
	if (jsonObject->TryGetNumberField(TEXT("TotalScore"), value))
	{
		outData.TotalScore = static_cast<float>(value);
	}

    // 4. 배열
    outData.PlayablePlayers.Reset();

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
        			outData.PlayablePlayers.Add(
						static_cast<EPlayablePlayer>(enumValue)
					);
        		}
        	}
        }
    }

    return true;
}
