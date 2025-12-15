#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EUIPopUpType : uint8
{
	Title,
	List,
	Calculator,
	Manual,
	ListDetail
};