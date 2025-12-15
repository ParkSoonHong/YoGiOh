// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Base/UiPopUpBase.h"
#include "TitleUI.generated.h"

UCLASS()
class YOGIOH_API UTitleUI : public UUiPopUpBase
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_DeckList;
	// 전방선언과 이 앞에 class 부르는것의 차이 알아보기.

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Dual;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Roll;

	UFUNCTION()
	void OnDeckListButtonClicked();

	UFUNCTION()
	void OnDualButtonClicked();

	UFUNCTION()
	void OnRollButtonClicked();
};
