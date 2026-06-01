// Fill out your copyright notice in the Description page of Project Settings.


#include "User/Manager/UserManager.h"

void UUserManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LoadAllUsers();
}

bool UUserManager::LoadAllUsers()
{
	userMap.Reset();
	
	if (!repository.LoadAllUser(userMap))
	{
		UE_LOG(LogTemp,Error,TEXT("LoadAll Failed"));
		return false;
	}
	return  true;
}

void UUserManager::SaveUser()
{
	if (userMap.IsEmpty())
	{
		UE_LOG(LogTemp,Error,TEXT("User Map is Empty"));
		return;
	}
	
	if (!repository.SaveUser(currentUser))
	{
		UE_LOG(LogTemp,Error,TEXT("SaveUser Failed"));
	}
}

void UUserManager::UpdateUser()
{
}

void UUserManager::FindUser(const FString& userID)
{
}
