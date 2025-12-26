
#include "Deck/Manager/DeckManagerHelper.h"
#include "Deck/Manager/DeckManager.h"

#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include  "Engine/Texture2D.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Common/Base/EEditableTextType.h"
#include "Modules/ModuleManager.h"
#include "Misc/FileHelper.h"


void DeckManagerHelper::Initialize(class UDeckManager* InManager, const FDeckSaveData& InData)
{
	Manager = InManager;
	WorkingData = InData;
	PendingExternalImagePath.Empty();
	CachedBrush.Reset();
	Recalculate();
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

void DeckManagerHelper::SetStatBySlider(EDeckStatType Type, float SliderValue)
{
	uint8 Value = FMath::RoundToInt(SliderValue * 10.f);

	switch (Type)
	{
	case EDeckStatType::Deployment:    WorkingData.Deployment = Value; break;
	case EDeckStatType::Breakthrough:  WorkingData.Breakthrough = Value; break;
	case EDeckStatType::Retention:     WorkingData.Retention = Value; break;
	case EDeckStatType::Recovery:      WorkingData.Recovery = Value; break;
	case EDeckStatType::Control:       WorkingData.Control = Value; break;
	case EDeckStatType::Flexibility:   WorkingData.Flexibility = Value; break;
	case EDeckStatType::BasePower:     WorkingData.BasePower = FMath::Clamp(Value, 0, 30); break;
	case EDeckStatType::RelativeA:     WorkingData.RelativeA = FMath::Clamp(Value, 0, 5); break;
	case EDeckStatType::RelativeB:     WorkingData.RelativeB = FMath::Clamp(Value, 0, 5); break;
	}

	Recalculate();
}

void DeckManagerHelper::SetText(const FString& Text, const EEditableTextType TextType)
{

	switch (TextType)
	{
	case  EEditableTextType::Comment:  WorkingData.Comment = Text; break;
	case  EEditableTextType::DeckName: WorkingData.DeckName = Text; break;
	}
}

void DeckManagerHelper::SetOwner(EDeckOwner Owner)
{
	WorkingData.Owner = Owner;
}

const FDeckSaveData& DeckManagerHelper::GetData() const
{
	return WorkingData;
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

FText DeckManagerHelper::GetTotalScoreText() const
{
	return FText::Format(
		NSLOCTEXT("Deck", "Score", "{0} / 100"),
		FText::AsNumber(WorkingData.TotalScore)
	);
}

bool DeckManagerHelper::Save(FString& OutError)
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

		WorkingData.ThumbnailImagePath = TEXT("DeckImages/") + FileName;
		PendingExternalImagePath.Empty();
	}

	return Manager->SaveDeck(OutError, WorkingData);
}

void DeckManagerHelper::Recalculate()
{
	WorkingData.TotalScore 
	= WorkingData.Deployment 
	+ WorkingData.Breakthrough 
	+ WorkingData.Retention
	+ WorkingData.Recovery 
	+ WorkingData.Control 
	+ WorkingData.Flexibility 
	+ WorkingData.BasePower 
	+ WorkingData.RelativeA 
	+ WorkingData.RelativeB;
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

	if (!WorkingData.ThumbnailImagePath.IsEmpty())
	{
		return FPaths::ProjectSavedDir() / WorkingData.ThumbnailImagePath;
	}

	return FString();
}
