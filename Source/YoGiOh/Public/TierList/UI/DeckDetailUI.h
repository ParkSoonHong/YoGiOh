// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Popup/UiPopUpBase.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Manager/DeckManagerHelper.h"
#include "DeckDetailUI.generated.h"


enum class EDeckFieldType : uint8;
class UButton;
class UComboBoxString;
class UEditableText;
class UTextBlock;
class UImage;
class UTexture2D;

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
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D * DeckBaseImage;
private:
	
	UFUNCTION()
	void OnDeckOwnerSelected( FString SelectedItem, ESelectInfo::Type SelectionType);
	
	// ComboBox 초기화
	void InitializeDeckOwnerComboBox();
	
private:
	void InitializeUI();
	void InitializeStatEditableTextBox(UEditableText* TextBox);
	void BindUIEvents();
	
	void RefreshUI();
	void RefreshTotalScoreUI();
	
	void UpdateStat(EDeckStatType StatType,float StatScore);

	void UpdateField(EDeckFieldType FieldType,const FString & FieldText);
	
	void UpdateStatEditableTextBox(UEditableText* TextBox, float Value);
	
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
