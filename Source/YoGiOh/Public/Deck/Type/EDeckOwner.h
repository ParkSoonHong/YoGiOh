#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDeckOwner : uint8
{
	PLAYERA UMETA(DisplayName = "순홍"),
	PLAYERB UMETA(DisplayName = "광석"),
	PLAYERC UMETA(DisplayName = "영배"),
};
