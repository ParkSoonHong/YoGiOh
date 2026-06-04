// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UserImageImpoter.generated.h"

/**
 * 
 */
UCLASS()
class YOGIOH_API UUserImageImpoter : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	bool ImportUserImage(FString& OutSavedPath, UTexture2D*& OutTexture);

	UTexture2D* LoadTextureFromFile(const FString& FilePath);
	
	UTexture2D* LoadUserImage(const FString& FileName);
private:

	bool OpenImageDialog(FString& OutSelectedPath);

	bool CopyImageToSavedFolder(const FString& SourcePath,FString& OutSavedPath);
	
	FString saveDir = FPaths::ProjectSavedDir() / TEXT("CopyUserImages");
};
