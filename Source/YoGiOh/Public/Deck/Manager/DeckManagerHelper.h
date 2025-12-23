#pragma once

#include "CoreMinimal.h"
#include "Common/Base/EDeckOwner.h"
#include "Common/Base/EEditableTextType.h"
#include "Deck/Domain/DeckSaveData.h"
#include "Common/Base/EDeckStatType.h"
#include "Styling/SlateBrush.h"

class DeckManagerHelper
{
	
public:
	void Initialize(class UDeckManager* InManager, const FDeckSaveData& InData);

	/* ===== Input ===== */

	void RequestChangeThumbnail();
	void SetStatBySlider(EDeckStatType Type, float SliderValue);
	void SetText(const FString& Text, const EEditableTextType TextType);
	void SetOwner(EDeckOwner Owner);
	
	/* ===== Output ===== */

	const FDeckSaveData& GetData() const;
	FSlateBrush GetThumbnailBrush() const;
	FText GetTotalScoreText() const;

	/* ===== Save ===== */

	bool Save(FString& OutError);

	
private:
	void Recalculate();
	// 추후 전용 유틸 클래스로 분리 
	static UTexture2D* LoadTextureFromFile(const FString& FilePath);

	// 🔹 미리보기용 경로 선택
	FString GetPreviewImagePath() const;
private:
	class UDeckManager* Manager = nullptr;
	
	FDeckSaveData WorkingData; // 비정적 데이터 멤버 초기화 안되어있다고 뜸 Initialize 하면 될것같은데 이거 어디서 하나?

	/** 파일 탐색기로 고른 외부 이미지 (아직 저장 안 됨) */
	FString PendingExternalImagePath;

	/** Slate 캐시 */
	mutable TSharedPtr<FSlateBrush> CachedBrush;
	mutable FString CachedBrushPath;
};
