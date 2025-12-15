// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Manager/UiPopUpManager.h"
#include "Common/Base/UiPopUpBase.h"
#include "Common/Base/UIPopUpType.h"

void UUiPopUpManager::BackInput()
{
	// Popup이 있으면 Popup부터
	if (PopupStack.Num() > 0)
	{
		PopPopup();
		return;
	}

	// 2Popup 없고 Screen만 있으면
	if (CurrentScreen)
	{
		CurrentScreen->OnCloseRequest.Broadcast();
		return;
	}
}

void UUiPopUpManager::ShowScreen(EUIPopUpType Type)
{

}

void UUiPopUpManager::PushPopup(TSubclassOf<UUiPopUpBase> PopupClass)
{

}

void UUiPopUpManager::PopPopup()
{
	if (PopupStack.Num() == 0) return;

	UUiPopUpBase* Popup = PopupStack.Pop();
	Popup->RemoveFromParent();
}
