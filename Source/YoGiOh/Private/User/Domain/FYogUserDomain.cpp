#include "User/Domain/FYogUserDomain.h"


bool FYogUserDomain::SetField(EUserFieldType FieldType, const FString& Field)
{
	switch (FieldType)
	{
	case EUserFieldType::USERNAME: userData.userName = Field; return true;
	case EUserFieldType::IMAGEPATH: userData.imagePath = Field; return true;
	default:
		{
			UE_LOG(LogTemp,Warning,TEXT("SetField Failed"));
			return false;
		}
	}
}

bool FYogUserDomain::SetUserId(const FString& UserId)
{
	userData.userID = UserId;
	return true;
}

