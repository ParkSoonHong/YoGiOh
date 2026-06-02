// Fill out your copyright notice in the Description page of Project Settings.


#include "User/Manager/UserManager.h"

#include "Supabase/SupabaseManager.h"

void UUserManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

// 
void UUserManager::LodingStart()
{
	if (USupabaseManager* supabaseMgr = GetGameInstance()->GetSubsystem<USupabaseManager>())
	{
		supabaseMgr->OnUsersLoaded.AddUObject(this, &UUserManager::LoadingCompleted);
		supabaseMgr->OnUsersLoadFailed.AddUObject(this,&UUserManager::LoadingFailed);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Insert User Failed"));
	}
	
	ServerLoadAllUsers();
}

bool UUserManager::LocalLoadAllUsers()
{
	userMap.Reset();
	
	if (!repository.LoadAllUser(userMap))
	{
		UE_LOG(LogTemp,Error,TEXT("LoadAll Failed"));
		return false;
	}

	return  true;
}

bool UUserManager::ServerLoadAllUsers()
{
	userMap.Reset();
	if (USupabaseManager* supabaseMgr = GetGameInstance()->GetSubsystem<USupabaseManager>())
	{
		supabaseMgr->GetUsers();
		return true;
	}
	
	LocalLoadAllUsers();
	return false;
}

void UUserManager::LocalSaveUser()
{
	if (!repository.SaveUser(currentUser))
	{
		UE_LOG(LogTemp,Error,TEXT("SaveUser Failed"));
	}
	
	ServerSaveUser();
}

void UUserManager::LocalSaveAllUser()
{
	TArray<FYogUserDomain> userDomains;

	userMap.GenerateValueArray(userDomains);
	
	for (const FYogUserDomain& userDomain : userDomains)
	{
		if (!repository.SaveUser(userDomain))
		{
			UE_LOG(LogTemp,Error,TEXT("SaveUser Failed"));
		}	
	}
	
}

void UUserManager::ServerSaveUser()
{
	if (USupabaseManager* supabaseMgr = GetGameInstance()->GetSubsystem<USupabaseManager>())
	{
		supabaseMgr->InsertUser(currentUser);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Insert User Failed"));
	}
}


void UUserManager::UpdateUser()
{
}

const FYogUserDomain* UUserManager::FindUser(const FString& UserId)
{
	return userMap.Find(UserId);
}

// 완료 델리게이트 등록 함수 
void UUserManager::LoadingCompleted(const FUserMap& UserMap)
{
	userMap = UserMap;
	LocalSaveAllUser();
	OnUserLoadcompleted.Broadcast();
}

void UUserManager::LoadingFailed()
{
	if (!LocalLoadAllUsers())
	{
		UE_LOG(LogTemp,Error,TEXT("Load Failed"));
		return;
	}
	OnUserLoadcompleted.Broadcast();
}
