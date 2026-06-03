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
	void SetUserId();
	bool SetUserId(const FString& UserId);
	bool SetUserName(const FString& UserName);
	
	bool IsValid() const;
private:
	FYogUserData userData;
};
