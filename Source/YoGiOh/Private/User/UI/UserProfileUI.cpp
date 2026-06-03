// Fill out your copyright notice in the Description page of Project Settings.


#include "User/UI/UserProfileUI.h"

#include "Deck/Impoter/DeckImageImporter.h"
#include "System/Popup/Manager/UiPopUpManager.h"
#include "User/Manager/UserManager.h"

void UUserProfileUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	BindUIEvents();
}
void UUserProfileUI::BindUIEvents()
{
	if (Button_Back != nullptr) 
		Button_Back->OnClicked.AddDynamic(this,&UUserProfileUI::OnClickedBackButton);

	if (Button_Save != nullptr)
		Button_Save->OnClicked.AddDynamic(this,&UUserProfileUI::OnClickedSaveButton);

	if (Editable_UserName != nullptr)
		Editable_UserName->OnTextCommitted.AddDynamic(this,&UUserProfileUI::OnUserNameCommitted);
}


void UUserProfileUI::OnClickedImageButton()
{
	// 2026-06-24 여기부터시작
}

void UUserProfileUI::OnClickedSaveButton()
{
	if (UUserManager* userMgr =GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
	{
		userMgr->LocalSaveUser();
	}
	
	if (UUiPopUpManager* popupMgr =GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		popupMgr->PopPopup();
	}
}

void UUserProfileUI::OnClickedBackButton()
{
	if (UUiPopUpManager* popupMgr =GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		popupMgr->PopPopup();
	}
}

void UUserProfileUI::OnUserNameCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (UUserManager* userMgr =GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
	{
		userMgr->UpdateUserName(Text.ToString());
	}
}

