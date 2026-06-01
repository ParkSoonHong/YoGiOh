// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "User/Domain/FYogUserDomain.h"
#include "User/Repository/UserRepository.h"
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
	
	bool LoadAllUsers();
	void SaveUser();
	void UpdateUser();
	void FindUser(const FString& userID);
	
private:
	TMap<FString,FString> userMap;
	UserRepository repository;
	FYogUserDomain currentUser;
};
