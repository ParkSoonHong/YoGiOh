#pragma once
#include "User/Type/FUserTypes.h"

class FUserJsonSerializer
{
public:
	static bool TrySerialize(const FYogUserDomain& Domain, FString& OutJson);
	static bool TryDeserialize(const FString& Json, FYogUserDomain& Domain);
	
	static bool TryDeserializeArray(const FString& Json,FUserMap& OutUsers);
	
private:
	static bool TryDeserializeObject( const TSharedPtr<FJsonObject>& JsonObject,
	FYogUserDomain& Domain);
};
