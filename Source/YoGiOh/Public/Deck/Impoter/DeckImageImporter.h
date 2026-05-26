// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DeckImageImporter.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UDeckImageImporter : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	bool ImportDeckImage(FString& OutSavedPath, UTexture2D*& OutTexture);

	UTexture2D* LoadTextureFromFile(const FString& FilePath);
private:

	bool OpenImageDialog(FString& OutSelectedPath);

	bool CopyImageToSavedFolder(const FString& SourcePath,FString& OutSavedPath);

};
