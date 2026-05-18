// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Domain/DeckDomain.h"
#include "Deck/Domain/Specification/DeckNameSpecification.h"

DeckDomain::DeckDomain(const FDeckData& inData) : data(inData)
{
	//RecalculateScore();
}

DeckDomain::DeckDomain() 
{
	
}

bool DeckDomain::Rename(const FString& newName, FString& outError)
{
	DeckNameSpecification Spec;
	if (!Spec.IsSatisfiedBy(newName, outError))
	{
		return false;
	}

	data.deckName = newName;
	return true;
}

bool DeckDomain::IsValid(FString& outError) const
{
	DeckNameSpecification nameSpec;
	if (!nameSpec.IsSatisfiedBy(data.deckName, outError))
	{
		return false;
	}

	return true;
}

void DeckDomain::RecalculateScore()
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

FDeckData DeckDomain::ToSaveData() const
{
	return data;
}