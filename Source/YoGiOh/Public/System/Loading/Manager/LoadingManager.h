// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LoadingManager.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API ULoadingManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void LoadingStart();
	
	void LoadingEnd();
	
private:
	int8 LoadingCount;
};
