#include "User/Repository/UserRepository.h"

#include "User/Domain/FYogUserDomain.h"

bool UserRepository::SaveUser(const FYogUserDomain& userDomain)
{
	return true;
}

bool UserRepository::LoadAllUser(TMap<FString,FString>& OutUsers)
{
	return true;
}
