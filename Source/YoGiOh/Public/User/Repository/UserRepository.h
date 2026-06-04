#pragma once
#include "User/Domain/FYogUserDomain.h"

class UserRepository
{
public:
	bool LocalSaveUser(const FYogUserDomain& Domain);
	bool LoadAllUser(TMap<FString,FYogUserDomain>& OutUsers);
	
	FString GetUserFilePath(const FYogUserDomain& Domain) const;
private:
	FString saveDirectory = FPaths::ProjectSavedDir() / TEXT("Users");
};
