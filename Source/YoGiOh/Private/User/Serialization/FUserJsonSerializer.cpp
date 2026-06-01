#include "User/Serialization/FUserJsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"

bool FUserSerialization::TrySerialize(const FYogUserDomain& Domain, FString& outJson)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();

	jsonObject->SetStringField(TEXT("ImagePath"), Domain.GetUserImagePath());
	jsonObject->SetStringField(TEXT("UserName"), Domain.GetUserName());
	jsonObject->SetStringField(TEXT("UserId"),Domain.GetUserId());
	
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&outJson);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);
	return true;
}

bool FUserSerialization::TryDeserialize(const FString& json, FYogUserDomain& Domain)
{
	TSharedPtr<FJsonObject> jsonObject;
    TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(json);

    if (!FJsonSerializer::Deserialize(reader, jsonObject) || !jsonObject.IsValid())
    {
        return false;
    }

    // 2. 문자열은 TryGet
	FString OutString;
    jsonObject->TryGetStringField(TEXT("ImagePath"), OutString);
	Domain.SetField(EUserFieldType::IMAGEPATH,OutString);
	jsonObject->TryGetStringField(TEXT("UserName"), OutString);
	Domain.SetField(EUserFieldType::USERNAME,OutString);
	jsonObject->TryGetStringField(TEXT("UserId"), OutString);
	Domain.SetUserId(OutString);
  
    return true;
}
