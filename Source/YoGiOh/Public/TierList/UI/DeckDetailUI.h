// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Popup/UiPopUpBase.h"
#include "Deck/Type/EDeckOwner.h"
#include "Deck/Data/DeckData.h"
#include "Deck/Manager/DeckManagerHelper.h"
#include "DeckDetailUI.generated.h"


class UButton;
class UComboBoxString;
class UEditableText;
class UTextBlock;
class UImage;

UCLASS()
class YOGIOH_API UDeckDetailUI : public UUiPopUpBase
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:	
	
	void InitializeDetail(UDeckManager* Manager, const FDeckData& Data);

	UPROPERTY(meta=(BindWidget))
	UButton* Button_SaveButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_BackButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_DeckImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* Image_Player;
	
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ComboBox_DeckOwner;
	
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_DeckName;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Deployment;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_Deployment;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Breakthrough;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_Breakthrough;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Retention;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_Retention;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Recovery;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_Recovery;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Control;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_Control;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Flexibility;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_Flexibility;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_BasePower;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_BasePower;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_RelativeA;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_RelativeA;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_RelativeB;
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_RelativeB;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_TotalScore;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * Text_Rank;
	
	UPROPERTY(meta = (BindWidget))
	UEditableText* Editable_Comment;
private:
	
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

	void RefreshTotalScore(EDeckStatType statType, float statScore);
	// 바인딩 함수들
	UFUNCTION()
	void OnChangeImage();
	
	UFUNCTION()
	void OnClickedSaveButton();
	UFUNCTION()
	void OnClickedBackButton();

	UFUNCTION()
	void OnCommentCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnDeckNameCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
	// values 조정
	UFUNCTION()
	void OnDeploymentValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnBreakthroughValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnRetentionValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnRecoveryValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnControlValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnFlexibilityValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnBasePowerValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnRelativeAValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnRelativeBValueCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	
};
