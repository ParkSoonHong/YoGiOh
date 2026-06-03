#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EUIPopUpType : uint8
{
	TITLE,
	TIERLIST,
	TIERLISTDETAIL,
	CALCCULATOR,
	MANUAL,
	LODING,
	SYSTEM,
	USERPROFILE
};