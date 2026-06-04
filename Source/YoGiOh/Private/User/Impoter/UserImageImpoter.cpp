// Fill out your copyright notice in the Description page of Project Settings.


#include "User/Impoter/UserImageImpoter.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"

#include "Misc/FileHelper.h"

#include "Misc/Paths.h"

#include "HAL/FileManager.h"

#include "Engine/Texture2D.h"

bool UUserImageImpoter::ImportUserImage(FString& OutSavedPath, UTexture2D*& OutTexture)
{
	FString selectedPath;

	if (!OpenImageDialog(selectedPath))
	{
		return false;
	}
	if (!CopyImageToSavedFolder(selectedPath,OutSavedPath))
	{
		return false;
	}
	
	FString Path = FPaths::ProjectSavedDir() / TEXT("CopyUserImages") / OutSavedPath;
	OutTexture = LoadTextureFromFile(Path);
	
	return OutTexture != nullptr;
}

UTexture2D* UUserImageImpoter::LoadTextureFromFile(const FString& FilePath)
{
	if (FilePath.IsEmpty())
	{
		return nullptr;
	}

	TArray<uint8> fileData;

	if (!FFileHelper::LoadFileToArray(fileData,*FilePath))
	{
		return nullptr;
	}
	
	IImageWrapperModule& imageWrapperModule =
		FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	EImageFormat Format =  imageWrapperModule.DetectImageFormat( 
		fileData.GetData(),
		fileData.Num());

	TSharedPtr<IImageWrapper> imageWrapper = imageWrapperModule.CreateImageWrapper(Format);

	if (!imageWrapper.IsValid())
	{
		return nullptr;
	}

	if (!imageWrapper->SetCompressed(fileData.GetData(),fileData.Num()))
	{
		return nullptr;
	}

	TArray<uint8> rawData;

	if (!imageWrapper->GetRaw(ERGBFormat::BGRA,8,rawData))
	{
		return nullptr;
	}

	UTexture2D* texture =
		UTexture2D::CreateTransient(imageWrapper->GetWidth(),imageWrapper->GetHeight());

	if (!texture)
	{
		return nullptr;
	}

	void* textureData = texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);

	FMemory::Memcpy(textureData,rawData.GetData(),rawData.Num());

	texture->GetPlatformData()->Mips[0].BulkData.Unlock();

	texture->UpdateResource();

	return texture;	
}

UTexture2D* UUserImageImpoter::LoadUserImage(const FString& FileName)
{
	FString path = saveDir / FileName;
	return LoadTextureFromFile(path);
}

bool UUserImageImpoter::OpenImageDialog(FString& OutSelectedPath)
{
	IDesktopPlatform* desktopPlatform = FDesktopPlatformModule::Get();
	if (!desktopPlatform)
	{
		return false;
	}

	TArray<FString> outFiles;
	
	bool bOpened = desktopPlatform->OpenFileDialog(
			nullptr, // 부모 윈도우
			TEXT("Select Deck Image"), // 탐색기 제목
			TEXT(""),// 기본 폴더
			TEXT(""),// 기본 파일명
			TEXT("Image Files (*.png;*.jpg)|*.png;*.jpg"),
			EFileDialogFlags::None,
			outFiles
		);

	if (!bOpened || outFiles.Num() == 0)
	{
		return false;
	}

	OutSelectedPath = outFiles[0];

	return true;
}

bool UUserImageImpoter::CopyImageToSavedFolder(const FString& SourcePath, FString& OutSavedPath)
{
	if (!IFileManager::Get().MakeDirectory(*saveDir, true))
	{
		UE_LOG(LogTemp,Error,TEXT("Could not create Image directory %s"),*saveDir);
		return false;
	}
	
	FString extension = FPaths::GetExtension(SourcePath);
	
	FString fileName = FGuid::NewGuid().ToString(EGuidFormats::Digits) + TEXT(".") + extension;

	FString DestPath = saveDir / fileName;
	
	OutSavedPath = fileName;
	
	return IFileManager::Get().Copy(*DestPath,*SourcePath) == COPY_OK;
}
