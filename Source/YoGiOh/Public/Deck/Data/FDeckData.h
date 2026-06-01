// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDeckData.generated.h"

USTRUCT(BlueprintType)
struct FDeckData
{
	GENERATED_BODY()

	UPROPERTY()
	FString imagePath; // 대표 이미지 경로 (PNG/JPG)
	
	UPROPERTY()
	FString deckID; // 덱 아이디 -> 덱 이름 + 덱 주인 + 

	UPROPERTY()
	FString deckName; // 덱 이름

	UPROPERTY()
	FString deckOwner; // 덱 주인

	//UPROPERTY()
	//TSet<EPlayablePlayer> playablePlayers; // 플레이 가능한 플레이어
	
	UPROPERTY()
	float deployment = 0; // 전개

	UPROPERTY()
	float breakthrough = 0; // 돌파

	UPROPERTY()
	float retention = 0; // 유지력

	UPROPERTY()
	float recovery = 0; // 복구

	UPROPERTY()
	float control = 0; // 억제

	UPROPERTY()
	float flexibility = 0; // 유연

	UPROPERTY()
	float basePower = 0; // 태생

	UPROPERTY()
	float relativeA = 0; // 상대평가1

	UPROPERTY()
	float relativeB = 0; // 상대평가2

	UPROPERTY()
	FString comment; // 종합평
};
