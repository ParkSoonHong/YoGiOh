// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Base/YoGiOhGameModeBase.h"
#include "Common/Base/UIPopUpType.h"
#include "Common/Manager/UiPopUpManager.h"

void AYoGiOhGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	UUiPopUpManager * UiPopUpManager = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>();
	
	if (UiPopUpManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not UI POPUP"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Open UI POPUP"));
	}
	UiPopUpManager->PushPopup(EUIPopUpType::Title);
}
