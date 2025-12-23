// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class YOGIOH_API DeckNameSpecification
{
public:
	bool IsSatisfiedBy(const FString& Name, FString& OutError) const
	{
		if (Name.Len() == 0)
		{
			OutError = TEXT("덱 이름은 비어 있을 수 없습니다.");
			return false;
		}

		if (Name.Len() > 30)
		{
			OutError = TEXT("덱 이름은 30자를 초과할 수 없습니다.");
			return false;
		}

		return true;
	}
};
