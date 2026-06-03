// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Domain/FDeckDomain.h"

#include "Deck/Rules/Specification/DeckNameSpecification.h"
#include "Deck/Rules/Specification/DeckCommentSpecification.h"
#include "Deck/Rules/FDeckStatRule.h"
#include "Deck/Type/EDeckStatType.h"

FDeckDomain::FDeckDomain(const FDeckData& inData) : data(inData)
{
	//RecalculateScore();
}

FDeckDomain::FDeckDomain() 
{
	
}

float FDeckDomain::GetStatScore(EDeckStatType StatType) const
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

FString FDeckDomain::GetField(EDeckFieldType FieldType) const
{
	FString Error;
	switch (FieldType)
	{
	case EDeckFieldType::OWNERID : return data.deckOwner; 
	case EDeckFieldType::DECKNAME : return data.deckName;
	case EDeckFieldType::COMMENT : return data.comment;
	default:
		{
			UE_LOG(LogTemp,Error,TEXT("DeckDomain::GetField: Unknown deck Field type"))
		}
	}
	return Error;
}

bool FDeckDomain::SetStatScore(EDeckStatType StatType, float NewScore)
{
	if (!FDeckStatRule::IsValid(StatType,NewScore))
	{
		return false;
	}
	switch (StatType)
	{
	case EDeckStatType::DEPLOYMENT: data.deployment = NewScore;break; 
	case EDeckStatType::BREAKTHROUGH: data.breakthrough = NewScore;break;
	case EDeckStatType::RETENTION:  data.retention = NewScore;break;
	case EDeckStatType::RECOVERY:  data.recovery = NewScore;break;
	case EDeckStatType::CONTROL:  data.control = NewScore;break;
	case EDeckStatType::FLEXIBILITY:  data.flexibility = NewScore;break;
	case EDeckStatType::BASEPOWER:  data.basePower = NewScore;break;
	case EDeckStatType::RELATIVEA:  data.relativeA = NewScore;break;
	case EDeckStatType::RELATIVEB:  data.relativeB = NewScore;break;
	default:
		{
			UE_LOG(LogTemp,Error,TEXT("DeckDomain::SetStatScore: Unknown deck stat type"))
			return false;
		}
	}
	return true;
}

bool FDeckDomain::SetField(EDeckFieldType FieldType, const FString& Field)
{
	FString outError;
	
	switch (FieldType)
	{
		case EDeckFieldType::OWNERID : data.deckOwner = Field; break;
		case EDeckFieldType::DECKNAME :
			{
				if (!DeckNameSpecification::IsSatisfiedByName(Field, outError))
				{
					UE_LOG(LogTemp,Error,TEXT("SetField DeckName Error : %s"),*outError);
					return false;
				}
				data.deckName = Field; 
				break;
			}
		case EDeckFieldType::COMMENT : 
			{
				if (!DeckCommentSpecification::IsSatisfiedByComment(Field, outError))
				{
					UE_LOG(LogTemp,Error,TEXT("SetField DeckComment Error : %s"),*outError);
					return false;
				}
				data.comment = Field;  
				break;
			}
		
		default:
			{
				UE_LOG(LogTemp,Error,TEXT("DeckDomain::SetField: Unknown deck Field type"))
				return false;
			}
	}
	
	return  true;
}

bool FDeckDomain::SetPath(const FString& Path)
{
	// 검증 추가 
	data.imagePath = Path;
	return true;
}

bool FDeckDomain::SetDeckId()
{
	FString Error;
	
	data.deckID =  FGuid::NewGuid().ToString(EGuidFormats::Digits);
	return  true;
}

void FDeckDomain::SetDeckId(const FString& DeckId)
{
	data.deckID = DeckId;
}

bool FDeckDomain::Rename(const FString& newName, FString& outError)
{
	DeckNameSpecification Spec;
	if (!Spec.IsSatisfiedByName(newName, outError))
	{
		return false;
	}

	data.deckName = newName;
	return true;
}

bool FDeckDomain::IsValid() const
{
	FString outError;
	if (data.deckID.IsEmpty())
	{
		UE_LOG(LogTemp,Error,TEXT("IsValid DeckName Error : IsEmpty"));
		return false;
	}
	
	if (!DeckCommentSpecification::IsSatisfiedByComment(data.comment, outError))
	{
		UE_LOG(LogTemp,Error,TEXT("IsValid DeckComment Error : %s"),*outError);
		return false;
	}
	
	if (!DeckNameSpecification::IsSatisfiedByName(data.deckName, outError))
	{
		UE_LOG(LogTemp,Error,TEXT("IsValid DeckName Error : %s"),*outError);
		return false;
	}

	return true;
}

FDeckData FDeckDomain::ToSaveData() const
{
	return data;
}