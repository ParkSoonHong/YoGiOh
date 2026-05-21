#pragma once
#include "Deck/Type/EDeckRank.h"

class FDeckRankRules
{
public:	
	static EDeckRank GetRank (float TotalScore);
	static FString  GetRankText (EDeckRank TotalScore);
	
};
