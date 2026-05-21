// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class YOGIOH_API DeckNameSpecification
{
public:
	static bool IsSatisfiedByName(const FString& Name, FString& OutError);
};
