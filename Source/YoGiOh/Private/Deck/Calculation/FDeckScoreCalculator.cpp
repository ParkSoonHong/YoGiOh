#include "Deck/Calculation/FDeckScoreCalculator.h"
#include "Deck/Domain/FDeckDomain.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Type/EDeckStatType.h"

float FDeckScoreCalculator::TotalScoreCalculation(const FDeckData& Data)
{
	float totalScore = 
		Data.breakthrough + 
		Data.deployment +
		Data.retention+
		Data.recovery +
		Data.control +
		Data.flexibility +
		Data.basePower + 
		Data.relativeA +
		Data.relativeB;
	return totalScore;
}
