// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FYogUserData.generated.h"

USTRUCT(BlueprintType)
struct FYogUserData
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString imagePath;// 대표이미지 경로
	
	UPROPERTY()
	FString userID; // user식별ID
	
	UPROPERTY()
	FString userName; // 유저 이름
};

