// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "User/Repository/UserRepository.h"
#include "User/Type/FUserTypes.h"
#include "UserManager.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UUserManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void LodingStart();
	
	bool LocalLoadAllUsers();
	bool ServerLoadAllUsers();
	
	void SaveUser();
	void LocalSaveAllUser();
	void ServerSaveUser();
	
	void UpdateUserName(const FString& UserName);
	void UpdateUserImagePath(const FString& Path);

	bool TryGetUserIdByName(const FString& UserName,FString& OutUserId) const;
	bool TryGetUserNameById(const FString& UserId,FString& OutUserName) const;
	
	void LoadingCompleted(const FUserMap& UserMap);
	void LoadingFailed();
	
	DECLARE_MULTICAST_DELEGATE(FOnUserLoadcompleted);
	DECLARE_MULTICAST_DELEGATE(FOnUserInitialize);
	DECLARE_MULTICAST_DELEGATE(FOnUserUpdate);
	
	FOnUserLoadcompleted OnUserLoadcompleted;
	FOnUserInitialize OnUserInitialize;
	FOnUserUpdate OnUserUpdate;
	
	FYogUserDomain GetCurrentUserDomain() const {return currentUser;}
	TArray<FYogUserDomain> GetUsers() const;
	
	void CreateUserDomain();
	
private:
	void RebuildUserNameIndex();

	const FYogUserDomain* FindUser(const FString& UserId);
	TMap<FString,FYogUserDomain> userMap;
	TMap<FString,FString> userNameToId;
	UserRepository repository;
	FYogUserDomain currentUser;
};
