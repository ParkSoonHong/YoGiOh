// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Base/UiPopUpBase.h"
#include "Common/Base/EDeckOwner.h"
#include "Deck/Manager/DeckManagerHelper.h"
#include "DeckDetailUI.generated.h"


class UButton;
class UComboBoxString;
class UEditableText;
class USlider;
class UTextBlock;

UCLASS()
class YOGIOH_API UDeckDetailUI : public UUiPopUpBase
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_SaveButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_DeckImage;
	
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ComboBox_DeckOwner;
	
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_DeckName;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Deployment;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Deployment;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Breakthrough;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Breakthrough;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Retention;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Retention;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Recovery;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Recovery;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Control;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Control;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Flexibility;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Flexibility;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_BasePower;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_BasePower;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_RelativeA;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_RelativeA;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_RelativeB;
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_RelativeB;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_TotalScore;
	
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_Comment;
private:
	
	TUniquePtr<DeckManagerHelper> DeckHelper;
	
	UFUNCTION()
	void OnDeckOwnerSelected( FString SelectedItem, ESelectInfo::Type SelectionType);
	
private:
	// 선택된 Enum 값 저장
	EDeckOwner SelectedDeckOwner;

	// String을 Enum으로 변환하는 맵
	TMap<FString, EDeckOwner> StringToEnumMap;

	// Enum을 String으로 변환하는 맵
	TMap<EDeckOwner, FString> EnumToStringMap;

	// ComboBox 초기화
	void InitializeDeckOwnerComboBox();

public:
	// 선택된 Enum 값 가져오기
	UFUNCTION(BlueprintCallable, Category = "ComboBox")
	EDeckOwner GetSelectedDeckOwner() const { return SelectedDeckOwner; }

	// Enum 값으로 선택 설정
	UFUNCTION(BlueprintCallable, Category = "ComboBox")
	void SetSelectedDeckOwner(EDeckOwner NewOwner);
	
private:
	void BindUIEvents();
	
	void RefreshUI();
	
	void RefreshScore();

	// 바인딩 함수들
	UFUNCTION()
	void OnChangeImage();
	
	UFUNCTION()
	void OnSave();

	UFUNCTION()
	void OnCommentCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnDeckNameCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
	UFUNCTION()
	void OnDeploymentSliderChanged(float Value);
	UFUNCTION()
	void OnBreakthroughSliderChanged(float Value);
	UFUNCTION()
	void OnRetentionSliderChanged(float Value);
	UFUNCTION()
	void OnRecoverySliderChanged(float Value);
	UFUNCTION()
	void OnControlSliderChanged(float Value);
	UFUNCTION()
	void OnFlexibilitySliderChanged(float Value);
	UFUNCTION()
	void OnBasePowerSliderChanged(float Value);
	UFUNCTION()
	void OnRelativeASliderChanged(float Value);
	UFUNCTION()
	void OnRelativeBSliderChanged(float Value);
};
