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

	const FYogUserDomain* FindUser(const FString& UserId);
	
	void LoadingCompleted(const FUserMap& UserMap);
	void LoadingFailed();
	
	DECLARE_MULTICAST_DELEGATE(FOnUserLoadcompleted);
	DECLARE_MULTICAST_DELEGATE(FOnUserInitialize);
	
	FOnUserLoadcompleted OnUserLoadcompleted;
	FOnUserInitialize OnUserInitialize;
	
	FYogUserDomain GetCurrentUserDomain() const {return currentUser;}
	TArray<FYogUserDomain> GetUsers() const;
	
	void CreateUserDomain();
	
private:
	TMap<FString,FYogUserDomain> userMap;
	UserRepository repository;
	FYogUserDomain currentUser;
};
