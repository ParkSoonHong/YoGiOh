
#include "Deck/Manager/DeckManagerHelper.h"
#include "Deck/Manager/DeckManager.h"

#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include  "Engine/Texture2D.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "UI/Type/EEditableTextType.h"
#include "Modules/ModuleManager.h"
#include "Misc/FileHelper.h"


void DeckManagerHelper::Initialize(class UDeckManager* InManager)
{
	Manager = InManager;
	PendingExternalImagePath.Empty();
	CachedBrush.Reset();
}

void DeckManagerHelper::RequestChangeThumbnail()
{
	IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
	if (!Platform) return;

	TArray<FString> Files;
	if (Platform->OpenFileDialog(
		nullptr,
		TEXT("이미지 선택"),
		TEXT(""),
		TEXT(""),
		TEXT("Image Files (*.png;*.jpg)|*.png;*.jpg"),
		EFileDialogFlags::None,
		Files
	))
	{
		PendingExternalImagePath = Files[0];   // ⭐ 외부 경로 유지
		CachedBrush.Reset();                   // 미리보기 갱신
	}
}

void DeckManagerHelper::SetStatBySlider(EDeckStatType Type, float SliderValue, FDeckData& WorkingData)
{
	uint8 Value = FMath::RoundToInt(SliderValue * 10.f);

	switch (Type)
	{
	case EDeckStatType::DEPLOYMENT:    WorkingData.deployment = Value; break;
	case EDeckStatType::BREAKTHROUGH:  WorkingData.breakthrough = Value; break;
	case EDeckStatType::RETENTION:     WorkingData.retention = Value; break;
	case EDeckStatType::RECOVERY:      WorkingData.recovery = Value; break;
	case EDeckStatType::CONTROL:       WorkingData.control = Value; break;
	case EDeckStatType::FLEXIBILITY:   WorkingData.flexibility = Value; break;
	case EDeckStatType::BASEPOWER:     WorkingData.basePower = FMath::Clamp(Value, 0, 30); break;
	case EDeckStatType::RELATIVEA:     WorkingData.relativeA = FMath::Clamp(Value, 0, 5); break;
	case EDeckStatType::RELATIVEB:     WorkingData.relativeB = FMath::Clamp(Value, 0, 5); break;
	}

	Recalculate(WorkingData);
}

void DeckManagerHelper::SetText(const FString& Text, const EEditableTextType TextType,  FDeckData& WorkingData)
{
	switch (TextType)
	{
	case  EEditableTextType::Comment:  WorkingData.comment = Text; break;
	case  EEditableTextType::DeckName: WorkingData.deckName = Text; break;
	}
}

void DeckManagerHelper::SetOwner(EDeckOwner Owner,  FDeckData& WorkingData)
{
	//WorkingData.deckOwner = Owner;
}

FSlateBrush DeckManagerHelper::GetThumbnailBrush() const
{
	const FString PreviewPath = GetPreviewImagePath();
	if (PreviewPath.IsEmpty())
	{
		return FSlateBrush();
	}

	if (!CachedBrush.IsValid() || CachedBrushPath != PreviewPath)
	{
		CachedBrushPath = PreviewPath;
		CachedBrush = MakeShared<FSlateBrush>();

		if (UTexture2D* Tex = LoadTextureFromFile(PreviewPath))
		{
			// ❌ AddToRoot 제거
			CachedBrush->SetResourceObject(Tex);
			CachedBrush->ImageSize = FVector2D(256, 256);
		}
	}

	return *CachedBrush;
}
/*
EDeckTier DeckManagerHelper::CalculateTier(uint8 TotalScore)
{
	if (TotalScore >= 90) return EDeckTier::S;
	if (TotalScore >= 80) return EDeckTier::A;
	if (TotalScore >= 70) return EDeckTier::B;
	if (TotalScore >= 60) return EDeckTier::C;
	if (TotalScore >= 50) return EDeckTier::D;
	if (TotalScore >= 40) return EDeckTier::E;
	return EDeckTier::F;
}
*/
bool DeckManagerHelper::SaveImageConvert(FString& OutError, FDeckData& WorkingData)
{
	if (!Manager)
	{
		OutError = TEXT("DeckManager 없음");
		return false;
	}

	// 🔹 새 이미지가 있으면 Saved 폴더로 복사
	if (!PendingExternalImagePath.IsEmpty())
	{
		const FString Dir = FPaths::ProjectSavedDir() / TEXT("DeckImages");
		IFileManager::Get().MakeDirectory(*Dir, true);

		const FString FileName =
			FString::Printf(TEXT("deck_%s.png"), *FGuid::NewGuid().ToString());

		const FString DestPath = Dir / FileName;

		const uint32 Result = IFileManager::Get().Copy(
		*DestPath,
		*PendingExternalImagePath
		);

		if (Result != COPY_OK)
		{
			OutError = FString::Printf(TEXT("이미지 복사 실패 (Code: %u)"), Result);
			return false;
		}

		WorkingData.imagePath = TEXT("DeckImages/") + FileName;
		PendingExternalImagePath.Empty();
	}
	return  true;
	//return Manager->SaveDeck(OutError, WorkingData);
}

void DeckManagerHelper::Recalculate(FDeckData& WorkingData)
{
	WorkingData.totalScore 
	= WorkingData.deployment 
	+ WorkingData.breakthrough 
	+ WorkingData.retention
	+ WorkingData.recovery 
	+ WorkingData.control 
	+ WorkingData.flexibility 
	+ WorkingData.basePower 
	+ WorkingData.relativeA 
	+ WorkingData.relativeB;
}

UTexture2D* DeckManagerHelper::LoadTextureFromFile(const FString& FilePath)
{
	if (FilePath.IsEmpty())
	{
		return nullptr;
	}

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
	{
		return nullptr;
	}

	IImageWrapperModule& ImageWrapperModule =
		FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");

	EImageFormat ImageFormat =
		ImageWrapperModule.DetectImageFormat(FileData.GetData(), FileData.Num());

	if (ImageFormat == EImageFormat::Invalid)
	{
		return nullptr;
	}

	TSharedPtr<IImageWrapper> ImageWrapper =
		ImageWrapperModule.CreateImageWrapper(ImageFormat);

	if (!ImageWrapper.IsValid() ||
		!ImageWrapper->SetCompressed(FileData.GetData(), FileData.Num()))
	{
		return nullptr;
	}

	TArray64<uint8> RawData;
	if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, RawData))
	{
		return nullptr;
	}

	UTexture2D* Texture = UTexture2D::CreateTransient(
		ImageWrapper->GetWidth(),
		ImageWrapper->GetHeight(),
		PF_B8G8R8A8
	);

	void* TextureData =
		Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);

	FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());

	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
	Texture->UpdateResource();

	return Texture;
}

FString DeckManagerHelper::GetPreviewImagePath() const
{
	if (!PendingExternalImagePath.IsEmpty())
	{
		return PendingExternalImagePath;        // 아직 저장 안 된 외부 이미지
	}
/*
	if (!WorkingData.ThumbnailImagePath.IsEmpty())
	{
		return FPaths::ProjectSavedDir() / WorkingData.ThumbnailImagePath;
	}
*/
	return FString();
}
