// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Type/EDeckOwner.h"
#include "Deck/Type/EPlayablePlayer.h"
#include "DeckData.generated.h"

USTRUCT(BlueprintType)
struct FDeckData
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	FString ImagePath; // 대표 이미지 경로 (PNG/JPG)
	
	UPROPERTY()
	FString DeckID; // 덱 아이디

	UPROPERTY()
	FString DeckName; // 덱 이름

	UPROPERTY()
	EDeckOwner DeckOwner; // 덱 주인

	UPROPERTY()
	TSet<EPlayablePlayer> PlayablePlayers; // 플레이 가능한 플레이어
	
	UPROPERTY()
	float Deployment = 0; // 전개

	UPROPERTY()
	float Breakthrough = 0; // 돌파

	UPROPERTY()
	float Retention = 0; // 유지력

	UPROPERTY()
	float Recovery = 0; // 복구

	UPROPERTY()
	float Control = 0; // 억제

	UPROPERTY()
	float Flexibility = 0; // 유연

	UPROPERTY()
	float BasePower = 0; // 태생

	UPROPERTY()
	float RelativeA = 0; // 상대평가1

	UPROPERTY()
	float RelativeB = 0; // 상대평가2

	UPROPERTY()
	float TotalScore = 0; // 종합점수

	UPROPERTY()
	FString Comment; // 종합평
};
