// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/Type/EDeckOwner.h"
#include "Deck/Type/EPlayablePlayer.h"
#include "DeckSaveData.generated.h"

USTRUCT(BlueprintType)
struct FDeckSaveData
{
	GENERATED_BODY()

public:

	/** 대표 이미지 경로 (PNG/JPG) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ImagePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DeckName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDeckOwner DeckOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<EPlayablePlayer> PlayablePlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DeckID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "10"))
	uint8 Deployment = 0; // 전개

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "10"))
	uint8 Breakthrough = 0; // 돌파

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "10"))
	uint8 Retention = 0; // 유지력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "10"))
	uint8 Recovery = 0; // 복구

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "10"))
	uint8 Control = 0; // 억제

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "10"))
	uint8 Flexibility = 0; // 유연

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "30"))
	uint8 BasePower = 0; // 태생

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "5"))
	uint8 RelativeA = 0; // 상대평가1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "5"))
	uint8 RelativeB = 0; // 상대평가2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalScore = 0; // 종합점수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Comment;
};