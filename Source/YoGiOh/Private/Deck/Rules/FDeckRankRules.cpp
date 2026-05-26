#include "Deck/Rules/FDeckRankRules.h"

EDeckRank FDeckRankRules::GetRank(float TotalScore) 
{
	if (TotalScore >= 90)return EDeckRank::S;
	if (TotalScore >= 80) return EDeckRank::A;
	if (TotalScore >= 70) return EDeckRank::B;
	if (TotalScore >= 60) return EDeckRank::C;
	if (TotalScore >= 50) return EDeckRank::D;
	if (TotalScore >= 40) return EDeckRank::E;
	
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
