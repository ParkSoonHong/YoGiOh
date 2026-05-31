// Fill out your copyright notice in the Description page of Project Settings.


#include "Supabase/SupabaseManage.h"
#include "HttpModule.h"
#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

void USupabaseManage::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USupabaseManage::InsertDeck(const FDeckDomain& Domain)
{
	FString Url = baseUrl + TEXT("/rest/v1/") + table_Decks;

	FString json;
	if (!FDeckJsonSerializer::TrySerialize(Domain,json))
	{
		
	}

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("apikey"), apiKey);
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + apiKey);

	Request->SetContentAsString(json);

	Request->OnProcessRequestComplete().BindLambda(
		[this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("Insert Failed"));
				return;
			}

			UE_LOG(LogTemp, Warning, TEXT("Insert Success: %s"),
				*Response->GetContentAsString());
			
			//GetDecks();
		});

	Request->ProcessRequest();
}

void USupabaseManage::GetDecks()
{
	FString Url =
	baseUrl + TEXT("/rest/v1/")
	+ table_Decks
	+ TEXT("?select=*");

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));

	Request->SetHeader(TEXT("apikey"), apiKey);
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + apiKey);

	Request->OnProcessRequestComplete().BindLambda(
		[](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("Get Failed"));
				return;
			}

			FString Result = Response->GetContentAsString();

			UE_LOG(LogTemp, Warning,
				TEXT("Deck Data: %s"),
				*Result);
		});

	Request->ProcessRequest();
}

void USupabaseManage::DeleteDeck()
{
}

void USupabaseManage::InsertUser()
{
}

void USupabaseManage::GetUser()
{
}

void USupabaseManage::DeleteUser()
{
}
