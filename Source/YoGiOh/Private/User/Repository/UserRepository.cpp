#include "User/Repository/UserRepository.h"

#include "User/Domain/FYogUserDomain.h"
#include "User/Serialization/FUserJsonSerializer.h"

bool UserRepository::LocalSaveUser(const FYogUserDomain& Domain)
{
	FString json;
	if (!FUserJsonSerializer::TrySerialize(Domain,json))
	{
		return false;
	}
	
	IFileManager::Get().MakeDirectory(*saveDirectory, true);
	
	FString filePath = saveDirectory / Domain.GetUserId() + TEXT(".json");
	
	return FFileHelper::SaveStringToFile(json, *filePath);
}

bool UserRepository::LoadAllUser(TMap<FString,FYogUserDomain>& OutUsers)
{
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

		FYogUserDomain Domain;

		if (!FUserJsonSerializer::TryDeserialize(JsonString,Domain))
		{
			UE_LOG(LogTemp,Error,TEXT("Could not load Deck %s"),*FilePath);
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

FString UserRepository::GetUserFilePath(const FYogUserDomain& Domain) const
{
	FString filePath = saveDirectory / Domain.GetUserId() + TEXT(".json");
	
	return filePath;
}
