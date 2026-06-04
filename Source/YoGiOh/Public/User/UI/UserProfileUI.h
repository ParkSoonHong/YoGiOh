// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "System/Popup/UiPopUpBase.h"
#include "UserProfileUI.generated.h"


UCLASS()
class YOGIOH_API UUserProfileUI : public UUiPopUpBase
{
	GENERATED_BODY()
public:
	virtual  void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Save; 
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Back;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_UserImage;
	
	UPROPERTY(meta=(BindWidget))
	UEditableText* Editable_UserName;
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* userProfileBaseImage;
	
	UFUNCTION()
	void OnClickedImageButton();
	UFUNCTION()
	void OnClickedSaveButton();
	UFUNCTION()
	void OnClickedBackButton();
	
	UFUNCTION()
	void OnUserNameCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
	
	void InitializeUI();
	
private:
	void BindUIEvents();
};
