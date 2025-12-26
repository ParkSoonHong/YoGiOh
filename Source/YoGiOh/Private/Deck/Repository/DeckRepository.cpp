// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Repository/DeckRepository.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"

bool DeckRepository::SaveToJson(const FString& FilePath, const FDeckSaveData& Data)
{
	/*
	*FString Json;
	FJsonObjectConverter::UStructToJsonObjectString(Data, Json);
	return FFileHelper::SaveStringToFile(Json, *FilePath);
	 */
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	JsonObject->SetStringField(TEXT("DeckName"), Data.DeckName);
	JsonObject->SetStringField(TEXT("ThumbnailImagePath"), Data.ThumbnailImagePath);
	JsonObject->SetNumberField(TEXT("Owner"), static_cast<int32>(Data.Owner));

	// Stats
	JsonObject->SetStringField(TEXT("DeckID"), Data.DeckID);
	JsonObject->SetNumberField(TEXT("Deployment"), Data.Deployment);
	JsonObject->SetNumberField(TEXT("Breakthrough"), Data.Breakthrough);
	JsonObject->SetNumberField(TEXT("Retention"), Data.Retention);
	JsonObject->SetNumberField(TEXT("Recovery"), Data.Recovery);
	JsonObject->SetNumberField(TEXT("Control"), Data.Control);
	JsonObject->SetNumberField(TEXT("Flexibility"), Data.Flexibility);
	JsonObject->SetNumberField(TEXT("BasePower"), Data.BasePower);
	JsonObject->SetNumberField(TEXT("RelativeA"), Data.RelativeA);
	JsonObject->SetNumberField(TEXT("RelativeB"), Data.RelativeB);
	JsonObject->SetNumberField(TEXT("TotalScore"), Data.TotalScore);

	JsonObject->SetStringField(TEXT("Comment"), Data.Comment);

	// PlayablePlayers
	TArray<TSharedPtr<FJsonValue>> PlayerArray;
	for (EPlayablePlayer Player : Data.PlayablePlayers)
	{
		PlayerArray.Add(MakeShared<FJsonValueNumber>(static_cast<int32>(Player)));
	}
	JsonObject->SetArrayField(TEXT("PlayablePlayers"), PlayerArray);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return FFileHelper::SaveStringToFile(OutputString, *FilePath);
}


bool DeckRepository::LoadFromJson(const FString& FilePath, FDeckSaveData& OutData)
{
	/*
	*FString Json;
	if (!FFileHelper::LoadFileToString(Json, *FilePath)) return false;
	return FJsonObjectConverter::JsonObjectStringToUStruct(Json, &OutData);
	 */
	OutData = FDeckSaveData();

    FString JsonString;
    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        return false;
    }

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        return false;
    }

    // ⭐ 2. 문자열은 TryGet
    JsonObject->TryGetStringField(TEXT("DeckName"), OutData.DeckName);
    JsonObject->TryGetStringField(TEXT("ThumbnailImagePath"), OutData.ThumbnailImagePath);
    JsonObject->TryGetStringField(TEXT("DeckID"), OutData.DeckID);
    JsonObject->TryGetStringField(TEXT("Comment"), OutData.Comment);

    // ⭐ 3. 숫자 필드
    int32 OwnerInt = 0;
    JsonObject->TryGetNumberField(TEXT("Owner"), OwnerInt);
    OutData.Owner = static_cast<EDeckOwner>(OwnerInt);

    JsonObject->TryGetNumberField(TEXT("Deployment"), OutData.Deployment);
    JsonObject->TryGetNumberField(TEXT("Breakthrough"), OutData.Breakthrough);
    JsonObject->TryGetNumberField(TEXT("Retention"), OutData.Retention);
    JsonObject->TryGetNumberField(TEXT("Recovery"), OutData.Recovery);
    JsonObject->TryGetNumberField(TEXT("Control"), OutData.Control);
    JsonObject->TryGetNumberField(TEXT("Flexibility"), OutData.Flexibility);
    JsonObject->TryGetNumberField(TEXT("BasePower"), OutData.BasePower);
    JsonObject->TryGetNumberField(TEXT("RelativeA"), OutData.RelativeA);
    JsonObject->TryGetNumberField(TEXT("RelativeB"), OutData.RelativeB);
    JsonObject->TryGetNumberField(TEXT("TotalScore"), OutData.TotalScore);

    // ⭐ 4. 배열
    OutData.PlayablePlayers.Reset();

    const TArray<TSharedPtr<FJsonValue>>* PlayerArray;
    if (JsonObject->TryGetArrayField(TEXT("PlayablePlayers"), PlayerArray))
    {
        for (const TSharedPtr<FJsonValue>& Value : *PlayerArray)
        {
            int32 PlayerInt = static_cast<int32>(Value->AsNumber());
            OutData.PlayablePlayers.Add(static_cast<EPlayablePlayer>(PlayerInt));
        }
    }

    return true;
}
