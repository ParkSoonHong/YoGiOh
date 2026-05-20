#pragma once

#include "CoreMinimal.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Type/EDeckOwner.h"
#include "UI/Type/EEditableTextType.h"
#include "Deck/Type/EDeckStatType.h"
#include "Styling/SlateBrush.h"

class DeckManagerHelper
{
	
public:
	void Initialize(class UDeckManager* InManager);

	/* ===== Input ===== */

	void RequestChangeThumbnail();
	static void SetStatBySlider(EDeckStatType Type, float SliderValue,  FDeckData& WorkingData);
	static void SetText(const FString& Text, const EEditableTextType TextType,  FDeckData& WorkingData);
	void SetOwner(EDeckOwner Owner,  FDeckData& WorkingData);
	
	/* ===== Output ===== */

	static void Recalculate(FDeckData& WorkingData);
	FSlateBrush GetThumbnailBrush() const;
	//static EDeckTier CalculateTier(uint8 TotalScore);

	/* ===== Save ===== */

	bool SaveImageConvert(FString& OutError, FDeckData& WorkingData);
	
private:
	// 추후 전용 유틸 클래스로 분리 
	static UTexture2D* LoadTextureFromFile(const FString& FilePath);

	// 🔹 미리보기용 경로 선택
	FString GetPreviewImagePath() const;
private:
	class UDeckManager* Manager = nullptr;
	
	/** 파일 탐색기로 고른 외부 이미지 (아직 저장 안 됨) */
	FString PendingExternalImagePath;

	/** Slate 캐시 */
	mutable TSharedPtr<FSlateBrush> CachedBrush;
	mutable FString CachedBrushPath;
};
