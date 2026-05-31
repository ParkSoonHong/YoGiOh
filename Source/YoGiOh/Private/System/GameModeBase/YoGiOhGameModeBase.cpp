// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GameModeBase/YoGiOhGameModeBase.h"
#include "System/Popup/Manager/UiPopUpManager.h"
#include "System/Popup/Type/UIPopUpType.h" 

void AYoGiOhGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (UUiPopUpManager* PopupMgr =
	   GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		//PopupMgr->PushPopup(EUIPopUpType::Loading);
	}
/*
	if (ULoadingManager* LoadingMgr =
		GetGameInstance()->GetSubsystem<ULoadingManager>())
	{
		LoadingMgr->StartLoading();
	}
	*/
}
