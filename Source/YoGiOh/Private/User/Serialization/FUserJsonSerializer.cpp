#include "User/Serialization/FUserJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"

bool FUserJsonSerializer::TrySerialize(const FYogUserDomain& Domain, FString& OutJson)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();

	jsonObject->SetStringField(TEXT("ImagePath"), Domain.GetUserImagePath());
	jsonObject->SetStringField(TEXT("UserName"), Domain.GetUserName());
	jsonObject->SetStringField(TEXT("UserId"),Domain.GetUserId());
	
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&OutJson);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);
	return true;
}

bool FUserJsonSerializer::TryDeserialize(const FString& Json, FYogUserDomain& Domain)
{
	TSharedPtr<FJsonObject> jsonObject;
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Json);

    if (!FJsonSerializer::Deserialize(reader, jsonObject) || !jsonObject.IsValid())
    {
        return false;
    }
  
    return TryDeserializeObject(jsonObject, Domain);
}


bool FUserJsonSerializer::TryDeserializeObject(const TSharedPtr<FJsonObject>& JsonObject, FYogUserDomain& Domain)
{
	if (!JsonObject.IsValid())
	{
		return false;
	}

	FString outString;

	JsonObject->TryGetStringField(TEXT("ImagePath"), outString);
	Domain.SetField(EUserFieldType::IMAGEPATH, outString);

	JsonObject->TryGetStringField(TEXT("UserName"), outString);
	Domain.SetField(EUserFieldType::USERNAME, outString);

	JsonObject->TryGetStringField(TEXT("UserId"), outString);
	Domain.SetUserId(outString);

	return true;
}


bool FUserJsonSerializer::TryDeserializeArray(const FString& Json, FUserMap& OutUsers)
{
	OutUsers.Reset();

	TArray<TSharedPtr<FJsonValue>> JsonArray;

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);

	if (!FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		return false;
	}

	for (const TSharedPtr<FJsonValue>& Value : JsonArray)
	{
		if (!Value.IsValid())
		{
			continue;
		}
		TSharedPtr<FJsonObject> JsonObject = Value->AsObject();

		if (!JsonObject.IsValid())
		{
			continue;
		}
		
		FYogUserDomain Domain;

		if (!TryDeserializeObject(JsonObject, Domain))
		{
			continue;
		}

		const FString UserId = Domain.GetUserId();
		
		if (UserId.IsEmpty())
		{
			UE_LOG(LogTemp,Error,TEXT("UserId is empty"));
			continue;
		}
		OutUsers.Add(UserId,Domain);
	}

	return true;
}
