// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Domain/DeckDomain.h"
#include "Deck/Domain/Specification/DeckNameSpecification.h"

DeckDomain::DeckDomain(const FDeckSaveData& InData) :Data((InData))
{
	RecalculateScore();
}
bool DeckDomain::Rename(const FString& NewName, FString& OutError)
{
	DeckNameSpecification Spec;
	if (!Spec.IsSatisfiedBy(NewName, OutError))
	{
		return false;
	}

	Data.DeckName = NewName;
	return true;
}

bool DeckDomain::IsValid(FString& OutError) const
{
	DeckNameSpecification NameSpec;
	if (!NameSpec.IsSatisfiedBy(Data.DeckName, OutError))
	{
		return false;
	}

	return true;
}

void DeckDomain::RecalculateScore()
{
	Data.TotalScore =
		Data.Deployment +
		Data.Breakthrough +
		Data.Retention +
		Data.Recovery +
		Data.Control +
		Data.Flexibility +
		Data.BasePower +
		Data.RelativeA +
		Data.RelativeB;
}

FDeckSaveData DeckDomain::ToSaveData() const
{
	return Data;
}