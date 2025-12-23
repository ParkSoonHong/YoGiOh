// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Manager/DeckManager.h"
#include "Deck/Domain/DeckDomain.h"
#include "Deck/Repository/DeckRepository.h"

bool UDeckManager::CreateAndSaveDeck(const FDeckSaveData& InputData, FString& OutError)
{
	DeckDomain Domain(InputData);

	if (!Domain.IsValid(OutError))
	{
		UE_LOG(LogTemp, Warning, TEXT("Deck validation failed: %s"), *OutError);
		return false;
	}

	const FString FilePath =
		FPaths::ProjectSavedDir() / TEXT("Decks/Deck.json");

	if (!DeckRepository::SaveToJson(FilePath, Domain.ToSaveData()))
	{
		OutError = TEXT("덱 저장 실패");
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Deck saved successfully: %s"), *FilePath);
	return true;
}

bool UDeckManager::LoadDeck(const FString& FilePath, FDeckSaveData& OutData)
{
	if (!DeckRepository::LoadFromJson(FilePath, OutData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load deck from %s"), *FilePath);
		return false;
	}

	DeckDomain Domain(OutData);
	FString Error;
	if (!Domain.IsValid(Error))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded deck invalid: %s"), *Error);
	}

	return true;
}

bool UDeckManager::SaveDeck(FString& OutError, const FDeckSaveData& Data)
{
	// 1. JSON Object 생성
	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();

	Root->SetNumberField(TEXT("Deployment"), Data.Deployment);
	Root->SetNumberField(TEXT("Breakthrough"), Data.Breakthrough);
	Root->SetNumberField(TEXT("Retention"), Data.Retention);
	Root->SetNumberField(TEXT("Recovery"), Data.Recovery);
	Root->SetNumberField(TEXT("Control"), Data.Control);
	Root->SetNumberField(TEXT("Flexibility"), Data.Flexibility);
	Root->SetNumberField(TEXT("BasePower"), Data.BasePower);
	Root->SetNumberField(TEXT("RelativeA"), Data.RelativeA);
	Root->SetNumberField(TEXT("RelativeB"), Data.RelativeB);
	Root->SetNumberField(TEXT("TotalScore"), Data.TotalScore);

	Root->SetStringField(TEXT("Comment"), Data.Comment);
	Root->SetStringField(TEXT("ThumbnailImagePath"), Data.ThumbnailImagePath);

	// 2. JSON → String
	FString Output;
	TSharedRef<TJsonWriter<>> Writer =
		TJsonWriterFactory<>::Create(&Output);

	if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
	{
		OutError = TEXT("JSON 직렬화 실패");
		return false;
	}

	// 3. 디렉토리 생성
	const FString SavePath = GetSaveFilePath();
	IFileManager::Get().MakeDirectory(*FPaths::GetPath(SavePath), true);

	// 4. 파일 저장
	if (!FFileHelper::SaveStringToFile(Output, *SavePath))
	{
		OutError = TEXT("파일 저장 실패");
		return false;
	}

	return true;
}

FString UDeckManager::GetSaveFilePath() const
{
	return FPaths::ProjectSavedDir() / TEXT("Deck/deck_data.json");
}
