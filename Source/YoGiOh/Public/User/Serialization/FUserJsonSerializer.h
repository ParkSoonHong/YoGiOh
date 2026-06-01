#pragma once
#include "User/Domain/FYogUserDomain.h"

class FUserSerialization
{
public:
	static  bool TrySerialize(const FYogUserDomain& Domain, FString& outJson);
	static  bool TryDeserialize(const FString& json, FYogUserDomain& Domain);
};
