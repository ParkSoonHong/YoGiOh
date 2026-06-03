// Fill out your copyright notice in the Description page of Project Settings.


#include "Supabase/SupabaseManager.h"
#include "HttpModule.h"
#include "Deck/Serialization/DeckJsonSerializer.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "User/Serialization/FUserJsonSerializer.h"

void USupabaseManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USupabaseManager::InsertDeck(const FDeckDomain& Domain)
{
	FString Url = baseUrl + TEXT("/rest/v1/") + table_Decks;

	FString json;
	if (!FDeckJsonSerializer::TrySerialize(Domain,json))
	{
		// 에러
		return;
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
			
		});

	Request->ProcessRequest();
}

void USupabaseManager::GetDecks()
{
	FString Url = baseUrl + TEXT("/rest/v1/") + table_Decks + TEXT("?select=*");

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));

	Request->SetHeader(TEXT("apikey"), apiKey);
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + apiKey);

	Request->OnProcessRequestComplete().BindLambda(
		[this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid() || !EHttpResponseCodes::IsOk(Response->GetResponseCode()))
			{
				UE_LOG(LogTemp, Error, TEXT("Get Failed"));
				OnDecksLoadFailed.Broadcast();
				return;
			}

			FString result = Response->GetContentAsString();
			
			FDeckMap deckMap;
			if (!FDeckJsonSerializer::TryDeserializeArray(result,deckMap))
			{
				OnDecksLoadFailed.Broadcast();
				UE_LOG(LogTemp, Warning, TEXT("GetDecks Failed"));
				return;
			}
			OnDecksLoaded.Broadcast(deckMap);
			UE_LOG(LogTemp, Warning, TEXT("user Data: %s"), *result);
			
		});

	Request->ProcessRequest();
}

void USupabaseManager::DeleteDeck()
{
}

void USupabaseManager::InsertUser(const FYogUserDomain& Domain)
{
	FString Url = baseUrl + TEXT("/rest/v1/") + table_User;

	FString json;
	if (!FUserJsonSerializer::TrySerialize(Domain,json))
	{
		// 에러
		return;
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
		});

	Request->ProcessRequest();
}

void USupabaseManager::GetUsers()
{
	FString Url = baseUrl + TEXT("/rest/v1/") + table_User + TEXT("?select=*");

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));

	Request->SetHeader(TEXT("apikey"), apiKey);
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + apiKey);

	Request->OnProcessRequestComplete().BindLambda(
		[this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid() || !EHttpResponseCodes::IsOk(Response->GetResponseCode()))
			{
				UE_LOG(LogTemp, Error, TEXT("Get Failed"));
				OnUsersLoadFailed.Broadcast();
				return;
			}

			FString result = Response->GetContentAsString();

			FUserMap usersMap;
			if (!FUserJsonSerializer::TryDeserializeArray(result,usersMap))
			{
				OnUsersLoadFailed.Broadcast();
				UE_LOG(LogTemp, Warning, TEXT("Get Failed"));
				return;
			}
			
			UE_LOG(LogTemp, Warning,
				TEXT("user Data: %s"),
				*result);
			
			OnUsersLoaded.Broadcast(usersMap);
			
		});

	Request->ProcessRequest();
}

void USupabaseManager::DeleteUser()
{
}
