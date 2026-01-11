// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GameModeBase/YoGiOhGameModeBase.h"
#include "System/Popup/Manager/UiPopUpManager.h"
#include "System/Popup/UIPopUpType.h"

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
