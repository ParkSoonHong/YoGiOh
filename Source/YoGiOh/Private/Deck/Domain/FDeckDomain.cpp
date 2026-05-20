// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Domain/FDeckDomain.h"

#include "Deck/Calculation/FDeckScoreCalculator.h"
#include "Deck/Domain/Specification/DeckNameSpecification.h"
#include "Deck/Type/EDeckStatType.h"

FDeckDomain::FDeckDomain(const FDeckData& inData) : data(inData)
{
	//RecalculateScore();
}

FDeckDomain::FDeckDomain() 
{
	
}

float FDeckDomain::GetStatScore(const EDeckStatType StatType) const
{
	switch (StatType)
	{
		case EDeckStatType::DEPLOYMENT: return data.deployment;
		case EDeckStatType::BREAKTHROUGH: return data.breakthrough;
		case EDeckStatType::RETENTION: return data.retention;
		case EDeckStatType::RECOVERY: return data.recovery; 
		case EDeckStatType::CONTROL: return data.control; 
		case EDeckStatType::FLEXIBILITY: return data.flexibility;
		case EDeckStatType::BASEPOWER: return data.basePower;
		case EDeckStatType::RELATIVEA: return data.relativeA; 
		case EDeckStatType::RELATIVEB: return data.relativeB; 
		default:
		{
				UE_LOG(LogTemp,Error,TEXT("DeckDomain::GetStatScore: Unknown deck stat type"));
				return 0;
		}
	}
}

void FDeckDomain::SetStatScore(const EDeckStatType StatType, float NewScore)
{
	switch (StatType)
	{
	case EDeckStatType::DEPLOYMENT: data.deployment = NewScore;break; 
	case EDeckStatType::BREAKTHROUGH: data.breakthrough = NewScore;break;
	case EDeckStatType::RETENTION:  data.retention = NewScore;break;;
	case EDeckStatType::RECOVERY:  data.recovery = NewScore;break;; 
	case EDeckStatType::CONTROL:  data.control = NewScore;break;; 
	case EDeckStatType::FLEXIBILITY:  data.flexibility = NewScore;break;;
	case EDeckStatType::BASEPOWER:  data.basePower = NewScore;break;;
	case EDeckStatType::RELATIVEA:  data.relativeA = NewScore;break;; 
	case EDeckStatType::RELATIVEB:  data.relativeB = NewScore;break;; 
	default:
		{
			UE_LOG(LogTemp,Error,TEXT("DeckDomain::GetStatScore: Unknown deck stat type"))
		}
	}
	data.totalScore = FDeckScoreCalculator::TotalScroeCalculation(data);
}

bool FDeckDomain::Rename(const FString& newName, FString& outError)
{
	DeckNameSpecification Spec;
	if (!Spec.IsSatisfiedBy(newName, outError))
	{
		return false;
	}

	data.deckName = newName;
	return true;
}

bool FDeckDomain::IsValid(FString& outError) const
{
	DeckNameSpecification nameSpec;
	if (!nameSpec.IsSatisfiedBy(data.deckName, outError))
	{
		return false;
	}

	return true;
}

void FDeckDomain::RecalculateScore()
{
	data.totalScore =
		data.deployment +
		data.breakthrough +
		data.retention +
		data.recovery +
		data.control +
		data.flexibility +
		data.basePower +
		data.relativeA +
		data.relativeB;
}

FDeckData FDeckDomain::ToSaveData() const
{
	return data;
}