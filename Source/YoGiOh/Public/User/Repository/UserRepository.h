#pragma once
#include "User/Domain/FYogUserDomain.h"

class UserRepository
{
public:
	bool SaveUser(const FYogUserDomain& userDomain);
	bool LoadAllUser(TMap<FString,FString>& OutUsers);
};
