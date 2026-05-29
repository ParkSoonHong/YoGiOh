// Fill out your copyright notice in the Description page of Project Settings.


#include "USupabaseManager.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

void UUSupabaseManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	TestInsertDeck();
	
}

void UUSupabaseManager::TestInsertDeck()
{
	FString Url =
		BaseUrl + TEXT("/rest/v1/") + TableName;

	TSharedPtr<FJsonObject> JsonObject =
		MakeShared<FJsonObject>();

	JsonObject->SetStringField(TEXT("deck_name"), TEXT("BlueEyes"));
	JsonObject->SetStringField(TEXT("owner"), TEXT("Yugi"));
	JsonObject->SetNumberField(TEXT("total_score"), 95.5f);

	FString JsonString;

	TSharedRef<TJsonWriter<>> Writer =
		TJsonWriterFactory<>::Create(&JsonString);

	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("apikey"), ApiKey);
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + ApiKey);

	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindLambda(
		[this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("Insert Failed"));
				return;
			}

			UE_LOG(LogTemp, Warning,
				TEXT("Insert Success: %s"),
				*Response->GetContentAsString());
			
			TestGetDecks();
		});

	Request->ProcessRequest();
}

void UUSupabaseManager::TestGetDecks()
{
	FString Url =
	BaseUrl + TEXT("/rest/v1/")
	+ TableName
	+ TEXT("?select=*");

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));

	Request->SetHeader(TEXT("apikey"), ApiKey);
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + ApiKey);

	Request->OnProcessRequestComplete().BindLambda(
		[](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("Get Failed"));
				return;
			}

			FString Result =
				Response->GetContentAsString();

			UE_LOG(LogTemp, Warning,
				TEXT("Deck Data: %s"),
				*Result);
		});

	Request->ProcessRequest();
}
