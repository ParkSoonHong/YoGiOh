// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Repository/DeckRepository.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"

bool DeckRepository::SaveToJson(const FString& FilePath, const FDeckSaveData& Data)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	JsonObject->SetStringField(TEXT("DeckName"), Data.DeckName);
	JsonObject->SetStringField(TEXT("ThumbnailImagePath"), Data.ThumbnailImagePath);
	JsonObject->SetNumberField(TEXT("Owner"), static_cast<int32>(Data.Owner));

	// Stats
	JsonObject->SetNumberField(TEXT("Expansion"), Data.Deployment);
	JsonObject->SetNumberField(TEXT("Breakthrough"), Data.Breakthrough);
	JsonObject->SetNumberField(TEXT("Sustain"), Data.Retention);
	JsonObject->SetNumberField(TEXT("Recovery"), Data.Recovery);
	JsonObject->SetNumberField(TEXT("Suppression"), Data.Control);
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

	OutData.DeckName = JsonObject->GetStringField(TEXT("DeckName"));
	OutData.ThumbnailImagePath = JsonObject->GetStringField(TEXT("ThumbnailImagePath"));
	OutData.Owner = static_cast<EDeckOwner>(JsonObject->GetIntegerField(TEXT("Owner")));

	OutData.Deployment = JsonObject->GetIntegerField(TEXT("Expansion"));
	OutData.Breakthrough = JsonObject->GetIntegerField(TEXT("Breakthrough"));
	OutData.Retention = JsonObject->GetIntegerField(TEXT("Sustain"));
	OutData.Recovery = JsonObject->GetIntegerField(TEXT("Recovery"));
	OutData.Control = JsonObject->GetIntegerField(TEXT("Suppression"));
	OutData.Flexibility = JsonObject->GetIntegerField(TEXT("Flexibility"));
	OutData.BasePower = JsonObject->GetIntegerField(TEXT("BasePower"));
	OutData.RelativeA = JsonObject->GetIntegerField(TEXT("RelativeA"));
	OutData.RelativeB = JsonObject->GetIntegerField(TEXT("RelativeB"));
	OutData.TotalScore = JsonObject->GetIntegerField(TEXT("TotalScore"));
	OutData.Comment = JsonObject->GetStringField(TEXT("Comment"));

	OutData.PlayablePlayers.Empty();
	for (auto& Value : JsonObject->GetArrayField(TEXT("PlayablePlayers")))
	{
		OutData.PlayablePlayers.Add(static_cast<EPlayablePlayer>(Value->AsNumber()));
	}

	return true;
}
