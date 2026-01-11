#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDeckOwner : uint8
{
	PlayerA UMETA(DisplayName = "순홍"),
	PlayerB UMETA(DisplayName = "광석"),
	PlayerC UMETA(DisplayName = "영배"),
	//PlayerD UMETA(DisplayName = "혜진")
};
