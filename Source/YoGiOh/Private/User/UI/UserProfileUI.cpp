// Fill out your copyright notice in the Description page of Project Settings.


#include "User/UI/UserProfileUI.h"

#include "Deck/Impoter/DeckImageImporter.h"
#include "System/Popup/Manager/UiPopUpManager.h"
#include "User/Impoter/UserImageImpoter.h"
#include "User/Manager/UserManager.h"

void UUserProfileUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	BindUIEvents();
	
	if (UUserManager * userMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
	{
		userMgr->OnUserInitialize.AddUObject(this, &UUserProfileUI::InitializeUI);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
}
void UUserProfileUI::BindUIEvents()
{
	if (Button_Back != nullptr) 
		Button_Back->OnClicked.AddDynamic(this,&UUserProfileUI::OnClickedBackButton);

	if (Button_Save != nullptr)
		Button_Save->OnClicked.AddDynamic(this,&UUserProfileUI::OnClickedSaveButton);

	if (Button_UserImage != nullptr)
		Button_UserImage->OnClicked.AddDynamic(this,&UUserProfileUI::OnClickedImageButton);
	
	if (Editable_UserName != nullptr)
		Editable_UserName->OnTextCommitted.AddDynamic(this,&UUserProfileUI::OnUserNameCommitted);
}


void UUserProfileUI::OnClickedImageButton()
{
	if (UUserImageImpoter* imageImporter = GetGameInstance()->GetSubsystem<UUserImageImpoter>())
	{
		FString savedPath;
		UTexture2D* texture = nullptr;

		if (imageImporter->ImportUserImage(savedPath,texture))
		{
			if (UUserManager * userMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
			{
				userMgr->UpdateUserImagePath(savedPath);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
			}
			
			FButtonStyle btrStyle = Button_UserImage->GetStyle();
			btrStyle.Normal.SetResourceObject(texture);
			btrStyle.Hovered.SetResourceObject(texture);
			btrStyle.Pressed.SetResourceObject(texture);
		
			Button_UserImage->SetStyle(btrStyle);
		}
	}
}

void UUserProfileUI::OnClickedSaveButton()
{
	if (UUserManager* userMgr =GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
	{
		userMgr->SaveUser();
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

void UUserProfileUI::InitializeUI()
{
	if (Button_UserImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Button_UserImage is nullptr"));
		return;
	}
	
	if (userProfileBaseImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("userBaseImage is nullptr"));
		return;
	}
	
	FButtonStyle btrStyle = Button_UserImage->GetStyle();
	btrStyle.Normal.SetResourceObject(userProfileBaseImage);
	btrStyle.Hovered.SetResourceObject(userProfileBaseImage);
	btrStyle.Pressed.SetResourceObject(userProfileBaseImage);
	
	Button_UserImage->SetStyle(btrStyle);
	
	Editable_UserName->SetText(FText::GetEmpty());
}


