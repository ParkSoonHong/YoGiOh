// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class  SystemPopupType : uint8
{
   Message,
   Warning,
   Error,
   Confirm
};
