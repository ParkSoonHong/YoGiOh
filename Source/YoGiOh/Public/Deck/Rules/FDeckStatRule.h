#pragma once
#include "Deck/Type/EDeckStatType.h"

class FDeckStatRule
{
public:
	static float GetMin() {return 0.00f;}
	static float GetMax(EDeckStatType Type);
	static bool IsValid(EDeckStatType Type,float Value);
};
