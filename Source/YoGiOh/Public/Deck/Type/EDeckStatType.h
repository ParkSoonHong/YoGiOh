#pragma once

UENUM(BlueprintType)
enum class EDeckStatType : uint8
{
	Deployment,
	Breakthrough,
	Retention,
	Recovery,
	Control,
	Flexibility,
	BasePower,
	RelativeA,
	RelativeB
};