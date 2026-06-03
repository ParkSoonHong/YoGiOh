#include "User/Domain/FYogUserDomain.h"

#include "User/Rules/Specification/UserNameSpecification.h"


bool FYogUserDomain::SetField(EUserFieldType FieldType, const FString& Field)
{
	FString outError;
	switch (FieldType)
	{
	case EUserFieldType::USERNAME:
		{
			if (!UserNameSpecification::IsSatisfiedByName(Field,outError))
			{
				UE_LOG(LogTemp,Warning,TEXT("SetField UserNameError : %s"),*outError);	
				return false;
			}
			userData.userName = Field; 
			return true;
		}
	case EUserFieldType::IMAGEPATH: userData.imagePath = Field; return true;
	default:
		{
			UE_LOG(LogTemp,Warning,TEXT("SetField Failed"));
			return false;
		}
	}
}

void FYogUserDomain::SetUserId()
{
	userData.userID = FGuid::NewGuid().ToString(EGuidFormats::Digits);;
}

bool FYogUserDomain::SetUserId(const FString& UserId)
{
	userData.userID = UserId;
	return true;
}

bool FYogUserDomain::SetUserName(const FString& UserName)
{
	FString outError;
	if (!UserNameSpecification::IsSatisfiedByName(UserName,outError))
	{
		UE_LOG(LogTemp,Warning,TEXT("SetUserNameError : %s"),*outError);	
		return false;
	}
	userData.userName = UserName;
	return true;
}

bool FYogUserDomain::IsValid() const
{
	FString outError;
	if (userData.userID.IsEmpty())
	{
		UE_LOG(LogTemp,Error,TEXT("IsValid userID Error :IsEmpty"));
		return false;
	}
	
	if (!UserNameSpecification::IsSatisfiedByName(userData.userName,outError))
	{
		UE_LOG(LogTemp,Warning,TEXT("IsValid UserName Error : %s"),*outError);	
		return false;
	}
	
	return true;
}

