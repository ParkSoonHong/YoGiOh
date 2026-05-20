#include "FDeckStatRule.h"


float FDeckStatRule::GetMax(EDeckStatType Type)
{
	switch (Type)
	{
	case EDeckStatType::RELATIVEA: return 5.00f;
	case EDeckStatType::RELATIVEB: return 5.00f;
	case EDeckStatType::BASEPOWER: return 30.00f;
	default: return 10.0f;
	}
}

bool FDeckStatRule::IsValid(EDeckStatType Type, float Value)
{
	switch (Type)
	{
	case EDeckStatType::RELATIVEA: return Value >= 0.00f && Value <= 5.00f;
	case EDeckStatType::RELATIVEB: return Value >= 0.00f && Value <= 5.00f;
	case EDeckStatType::BASEPOWER: return Value >= 0.00f && Value <= 30.00f;
	default: return Value >= 0.00f && Value <= 30.00f;
	}
}
