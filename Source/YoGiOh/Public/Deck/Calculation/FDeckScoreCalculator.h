#pragma once

enum class EDeckStatType : uint8;
struct FDeckData;

class FDeckScoreCalculator
{
public:	
	// 스텟 계산해서 총 스코어 반환
	static float TotalScoreCalculation(const FDeckData& Data);
};

