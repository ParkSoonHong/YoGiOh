#pragma once
#include "User/Data/FYogUserData.h"
#include "User/Type/EUserFieldType.h"

class FYogUserDomain
{
public:	
	// ----- Get -----
	const FString& GetUserName() const {return userData.userName;};
	const FString& GetUserId() const  {return userData.userID;};
	const FString& GetUserImagePath() const  {return userData.imagePath;};
	// ----- Set -----
	bool SetField(EUserFieldType FieldType, const FString& Field);
	bool SetUserId(const FString& UserId);
private:
	FYogUserData userData;
};
