#include "Deck/Rules/FDeckRankRules.h"

EDeckRank FDeckRankRules::GetRank(float TotalScore) 
{
	if (TotalScore >= 85.66)return EDeckRank::S;
	if (TotalScore >= 71.38) return EDeckRank::A;
	if (TotalScore >= 57.1) return EDeckRank::B;
	if (TotalScore >= 42.82) return EDeckRank::C;
	if (TotalScore >= 28.54) return EDeckRank::D;
	if (TotalScore >= 14.26) return EDeckRank::E;
	
	return EDeckRank::F;
}

FString FDeckRankRules::GetRankText(EDeckRank TotalScore)
{
	switch (TotalScore)
	{
	case EDeckRank::S: return TEXT("S");
	case EDeckRank::A: return TEXT("A");
	case EDeckRank::B: return TEXT("B");
	case EDeckRank::C: return TEXT("C");
	case EDeckRank::D: return TEXT("D");
	case EDeckRank::E: return TEXT("E");
		
	default: return TEXT("F");
	}
}

const TArray<EDeckRank>& FDeckRankRules::GetRankOrder()
{
	static const TArray<EDeckRank> RankOrder =
	{
		EDeckRank::S,
		EDeckRank::A,
		EDeckRank::B,
		EDeckRank::C,
		EDeckRank::D,
		EDeckRank::E,
		EDeckRank::F
	};

	return RankOrder;
}
