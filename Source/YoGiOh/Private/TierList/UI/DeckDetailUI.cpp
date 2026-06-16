// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/DeckDetailUI.h"

#include <string>

#include "Deck/Type//EDeckOwner.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Deck/Impoter/DeckImageImporter.h"
#include "Deck/Manager/DeckManager.h"
#include "Deck/Rules/FDeckRankRules.h"
#include "Deck/Rules/FDeckStatRule.h"

#include "System/Popup/Manager/UiPopUpManager.h"
#include "User/Domain/FYogUserDomain.h"
#include "User/Manager/UserManager.h"

void UDeckDetailUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindUIEvents();
	
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->OnDeckTotatlScoreUpdate.AddUObject(this, &UDeckDetailUI::RefreshTotalScoreUI);
		deckMgr->OnDeckUpdate.AddUObject(this, &UDeckDetailUI::RefreshUI);
		deckMgr->OnDeckInitialize.AddUObject(this, &UDeckDetailUI::InitializeUI);
	}

	if (UUserManager * userMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
	{
		userMgr->OnUserUpdate.AddUObject(this, &UDeckDetailUI::InitializeDeckOwnerComboBox);
	}
	InitializeDeckOwnerComboBox();
	InitializeUI();
}

void UDeckDetailUI::InitializeDeckOwnerComboBox()
{
	if (!ComboBox_DeckOwner)
		return;

	// ComboBox 초기화
	ComboBox_DeckOwner->ClearOptions();
	TArray<FYogUserDomain> userDomains;
	if (UUserManager * userMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
	{
		userDomains = userMgr->GetUsers();
	}
	
	if (userDomains.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
		return;
	}
	
	for (const FYogUserDomain& userDomain : userDomains)
	{
		ComboBox_DeckOwner->AddOption(userDomain.GetUserName());
	}

	UE_LOG(LogTemp,Warning,TEXT("InitializeDeckOwnerComboBox"));
}

void UDeckDetailUI::InitializeUI()
{
	// 버튼 이미지 초기화
	if (Button_DeckImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Button_DeckImage is nullptr"));
		return;
	}
	
	if (DeckBaseImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckBaseImage is nullptr"));
		return;
	}
	FButtonStyle btrStyle = Button_DeckImage->GetStyle();
	btrStyle.Normal.SetResourceObject(DeckBaseImage);
	btrStyle.Hovered.SetResourceObject(DeckBaseImage);
	btrStyle.Pressed.SetResourceObject(DeckBaseImage);
	
	// 스텟 초기화
	Button_DeckImage->SetStyle(btrStyle);
	
	InitializeStatEditableTextBox(Editable_Deployment);
	InitializeStatEditableTextBox(Editable_Breakthrough);
	InitializeStatEditableTextBox(Editable_Retention);
	InitializeStatEditableTextBox(Editable_Recovery);
	InitializeStatEditableTextBox(Editable_Control);
	InitializeStatEditableTextBox(Editable_Flexibility);
	InitializeStatEditableTextBox(Editable_BasePower);
	InitializeStatEditableTextBox(Editable_RelativeA);
	InitializeStatEditableTextBox(Editable_RelativeB);
	Text_TotalScore->SetText(FText::FromString(TEXT("0.00")));
	
	//콤보박스 초기화
	ComboBox_DeckOwner->ClearSelection();
	
	Editable_DeckName->SetText(FText::GetEmpty());
	Editable_Comment->SetText(FText::GetEmpty());
	
	Text_Rank->SetText(FText::FromString("F"));
}

void UDeckDetailUI::UpdateStat(EDeckStatType StatType,float StatScore)
{
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->UpdateStatCurrentDeck(StatType,StatScore);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
}

void UDeckDetailUI::UpdateField(EDeckFieldType FieldType, const FString& FieldText)
{
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->UpdateFieldCurrentDeck(FieldType,FieldText);
	}
}

void UDeckDetailUI::RefreshUI()
{
	FDeckDomain domain;
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		domain = deckMgr->GetCurrentDeck();
	}
	
	if (Button_DeckImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Button_DeckImage is nullptr"));
		return;
	}
	
	if (DeckBaseImage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckBaseImage is nullptr"));
		return;
	}
	
	if (UDeckImageImporter* ImageService = GetGameInstance()->GetSubsystem<UDeckImageImporter>())
	{
		FString deckFileName = domain.GetImagePath();
		if (!deckFileName.IsEmpty())
		{
			UTexture2D * Thumbnail = ImageService->LoadDeckImage(deckFileName);
			FButtonStyle btrStyle = Button_DeckImage->GetStyle();
			btrStyle.Normal.SetResourceObject(Thumbnail);
			btrStyle.Hovered.SetResourceObject(Thumbnail);
			btrStyle.Pressed.SetResourceObject(Thumbnail);
			Button_DeckImage->SetStyle(btrStyle);
		}
	}
	
	UpdateStatEditableTextBox(Editable_Deployment,domain.GetStatScore(EDeckStatType::DEPLOYMENT));
	UpdateStatEditableTextBox(Editable_Breakthrough,domain.GetStatScore(EDeckStatType::BREAKTHROUGH));
	UpdateStatEditableTextBox(Editable_Retention,domain.GetStatScore(EDeckStatType::RETENTION));
	UpdateStatEditableTextBox(Editable_Recovery,domain.GetStatScore(EDeckStatType::RECOVERY));
	UpdateStatEditableTextBox(Editable_Control,domain.GetStatScore(EDeckStatType::CONTROL));
	UpdateStatEditableTextBox(Editable_Flexibility,domain.GetStatScore(EDeckStatType::FLEXIBILITY));
	UpdateStatEditableTextBox(Editable_BasePower,domain.GetStatScore(EDeckStatType::BASEPOWER));
	UpdateStatEditableTextBox(Editable_RelativeA,domain.GetStatScore(EDeckStatType::RELATIVEA));
	UpdateStatEditableTextBox(Editable_RelativeB,domain.GetStatScore(EDeckStatType::RELATIVEB));
	FString formatted  = FString::Printf(TEXT("%.2f"), domain.GetTotalScore());
	Text_TotalScore->SetText(FText::FromString(formatted) );
	
	//콤보박스 초기화
	if (UUserManager * userMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
	{
		FString OutUserName;
		if (userMgr->TryGetUserNameById(domain.GetField(EDeckFieldType::OWNERID),OutUserName))
		{
			ComboBox_DeckOwner->SetSelectedOption(OutUserName);
		}
	}
	
	
	Editable_DeckName->SetText(FText::FromString(domain.GetField(EDeckFieldType::DECKNAME)));
	Editable_Comment->SetText(FText::FromString(domain.GetField(EDeckFieldType::COMMENT)));
	
	EDeckRank rank = FDeckRankRules::GetRank(domain.GetTotalScore());
	Text_Rank->SetText(FText::FromString(FDeckRankRules::GetRankText(rank)));
}

void UDeckDetailUI::RefreshTotalScoreUI()
{
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		float totalScore = deckMgr->GetCurrentDeck().GetTotalScore();
		FString strFloat = FString::Printf(TEXT("%.2f"), totalScore);
		Text_TotalScore->SetText(FText::FromString(strFloat));
		
		EDeckRank Rank = FDeckRankRules::GetRank(totalScore);
		Text_Rank->SetText(FText::FromString(FDeckRankRules::GetRankText(Rank))); 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
}
void UDeckDetailUI::UpdateStatEditableTextBox(UEditableText* TextBox, float Value)
{
	if (TextBox == nullptr) return;
	
	FString formatted  = FString::Printf(TEXT("%.2f"), Value);
	TextBox->SetText(FText::FromString(formatted));
}

void UDeckDetailUI::InitializeStatEditableTextBox(UEditableText* TextBox)
{
	if (TextBox == nullptr) return;
	
	float minValue = FDeckStatRule::GetMin();
	FString formatted  = FString::Printf(TEXT("%.2f"), minValue);
	TextBox->SetText(FText::FromString(formatted));
}

// 바인딩
void UDeckDetailUI::BindUIEvents()
{
	//콤보박스들
	if (ComboBox_DeckOwner== nullptr) return;
	ComboBox_DeckOwner->OnSelectionChanged.AddDynamic(this, &UDeckDetailUI::OnDeckOwnerSelected);
	
	//버튼들
	if (Button_DeckImage == nullptr) return;
	Button_DeckImage->OnClicked.AddDynamic(this, &UDeckDetailUI::OnClickedImageButton);
	
	if (Button_Save == nullptr) return;
	Button_Save->OnClicked.AddDynamic(this, &UDeckDetailUI::OnClickedSaveButton);
	
	if (Button_Back == nullptr) return;
	Button_Back->OnClicked.AddDynamic(this, &UDeckDetailUI::OnClickedBackButton);
	
	//편집박스들
	if (Editable_Comment == nullptr) return;
	Editable_Comment->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnCommentCommitted);
	
	if (Editable_DeckName == nullptr) return;
	Editable_DeckName->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnDeckNameCommitted);
	
	if (Editable_Deployment == nullptr) return;
	Editable_Deployment->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnDeploymentValueCommitted);
	
	if (Editable_Breakthrough == nullptr) return;
	Editable_Breakthrough->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnBreakthroughValueCommitted);
	
	if (Editable_Retention == nullptr) return;
	Editable_Retention->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnRetentionValueCommitted);
	
	if (Editable_Recovery == nullptr) return;
	Editable_Recovery->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnRecoveryValueCommitted);
	
	if (Editable_Control == nullptr) return;
	Editable_Control->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnControlValueCommitted);
	
	if (Editable_Flexibility == nullptr) return;
	Editable_Flexibility->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnFlexibilityValueCommitted);
	
	if (Editable_BasePower == nullptr) return;
	Editable_BasePower->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnBasePowerValueCommitted);
	
	if (Editable_RelativeA == nullptr) return;
	Editable_RelativeA->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnRelativeAValueCommitted);

	if (Editable_RelativeB == nullptr) return;
	Editable_RelativeB->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnRelativeBValueCommitted);
}



// 이미지 변경
void UDeckDetailUI::OnClickedImageButton()
{
	if (UDeckImageImporter* imageImpoter =GetGameInstance()->GetSubsystem<UDeckImageImporter>())
	{
		FString savedPath;
		UTexture2D* texture = nullptr;

		if (imageImpoter->ImportDeckImage(savedPath,texture))
		{
			// Domain 저장
			if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
			{
				deckMgr->UpdateImagePath(savedPath);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
			}
			// 썸네일 표시
			FButtonStyle btrStyle = Button_DeckImage->GetStyle();
			btrStyle.Normal.SetResourceObject(texture);
			btrStyle.Hovered.SetResourceObject(texture);
			btrStyle.Pressed.SetResourceObject(texture);
		
			Button_DeckImage->SetStyle(btrStyle);
		}
	}
	
}

void UDeckDetailUI::OnClickedSaveButton()
{
	FString Error;
	
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		if (!deckMgr->LocalSaveDeck())
		{
			UE_LOG(LogTemp, Warning, TEXT("DackSave Failed"));
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
	
	if (UUiPopUpManager* PopupMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupMgr->PopPopup();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
}

void UDeckDetailUI::OnClickedBackButton()
{
	if (UUiPopUpManager* PopupMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupMgr->PopPopup();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
}
void UDeckDetailUI::OnDeckOwnerSelected( FString SelectedItem, ESelectInfo::Type SelectionType)
{
	UpdateField(EDeckFieldType::OWNERID,SelectedItem);
}

void UDeckDetailUI::OnCommentCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	UpdateField(EDeckFieldType::COMMENT,Text.ToString());
}

void UDeckDetailUI::OnDeckNameCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	UpdateField(EDeckFieldType::DECKNAME,Text.ToString());
}

void UDeckDetailUI::OnDeploymentValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float deploymentValue =  FCString::Atof(*Text.ToString());
	deploymentValue = FMath::Clamp(
		deploymentValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::DEPLOYMENT));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), deploymentValue);
	if (Editable_Deployment->GetText().ToString() != formatted )
	{
		Editable_Deployment->SetText(FText::FromString(formatted ));
		UE_LOG(LogTemp, Warning, TEXT("OnDeploymentValueCommitted"));
	}
	UpdateStat(EDeckStatType::DEPLOYMENT,deploymentValue);
}

void UDeckDetailUI::OnBreakthroughValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float breakthroghValue =  FCString::Atof(*Text.ToString());
	breakthroghValue = FMath::Clamp(
		breakthroghValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::BREAKTHROUGH));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), breakthroghValue);
	if (Editable_Breakthrough->GetText().ToString() != formatted )
	{
		Editable_Breakthrough->SetText(FText::FromString(formatted ));
		UE_LOG(LogTemp, Warning, TEXT("OnDeploymentValueCommitted"));
	}
	UpdateStat(EDeckStatType::BREAKTHROUGH,breakthroghValue);
}

void UDeckDetailUI::OnRetentionValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float retentionValue =  FCString::Atof(*Text.ToString());
	retentionValue = FMath::Clamp(
		retentionValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::RETENTION));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), retentionValue);
	if (Editable_Retention->GetText().ToString() != formatted )
	{
		Editable_Retention->SetText(FText::FromString(formatted ));
	}
	UpdateStat(EDeckStatType::RETENTION,retentionValue);
}

void UDeckDetailUI::OnRecoveryValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float recoveryValue =  FCString::Atof(*Text.ToString());
	recoveryValue = FMath::Clamp(
		recoveryValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::RECOVERY));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), recoveryValue);
	if (Editable_Recovery->GetText().ToString() != formatted )
	{
		Editable_Recovery->SetText(FText::FromString(formatted ));
	}
	UpdateStat(EDeckStatType::RECOVERY,recoveryValue);
}

void UDeckDetailUI::OnControlValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float controlValue =  FCString::Atof(*Text.ToString());
	controlValue = FMath::Clamp(
		controlValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::CONTROL));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), controlValue);
	if (Editable_Control->GetText().ToString() != formatted )
	{
		Editable_Control->SetText(FText::FromString(formatted ));
	}
	UpdateStat(EDeckStatType::CONTROL,controlValue);
}

void UDeckDetailUI::OnFlexibilityValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float flexibilityValue =  FCString::Atof(*Text.ToString());
	flexibilityValue = FMath::Clamp(
		flexibilityValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::FLEXIBILITY));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), flexibilityValue);
	if (Editable_Flexibility->GetText().ToString() != formatted )
	{
		Editable_Flexibility->SetText(FText::FromString(formatted ));
	}
	UpdateStat(EDeckStatType::FLEXIBILITY,flexibilityValue);
}

void UDeckDetailUI::OnBasePowerValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float basePowerValue =  FCString::Atof(*Text.ToString());
	basePowerValue = FMath::Clamp(
		basePowerValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::BASEPOWER));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), basePowerValue);
	if (Editable_BasePower->GetText().ToString() != formatted )
	{
		Editable_BasePower->SetText(FText::FromString(formatted ));
	}
	UpdateStat(EDeckStatType::BASEPOWER,basePowerValue);
}

void UDeckDetailUI::OnRelativeAValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float relativeAValue =  FCString::Atof(*Text.ToString());
	relativeAValue = FMath::Clamp(
		relativeAValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::RELATIVEA));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), relativeAValue);
	if (Editable_RelativeA->GetText().ToString() != formatted )
	{
		Editable_RelativeA->SetText(FText::FromString(formatted ));
	}
	UpdateStat(EDeckStatType::RELATIVEA,relativeAValue);
}

void UDeckDetailUI::OnRelativeBValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float relativeBValue =  FCString::Atof(*Text.ToString());
	relativeBValue = FMath::Clamp(
	relativeBValue, FDeckStatRule::GetMin(), FDeckStatRule::GetMax(EDeckStatType::RELATIVEB));
	
	FString formatted  = FString::Printf(TEXT("%.2f"), relativeBValue);
	if (Editable_RelativeB->GetText().ToString() != formatted )
	{
		Editable_RelativeB->SetText(FText::FromString(formatted ));
	}
	UpdateStat(EDeckStatType::RELATIVEB,relativeBValue);
}

