// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/DeckDetailUI.h"

#include <string>

#include "Deck/Type//EDeckOwner.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Deck/Calculation/FDeckScoreCalculator.h"
#include "Deck/Manager/DeckManager.h"

#include "System/Popup/Manager/UiPopUpManager.h"

void UDeckDetailUI::NativeConstruct()
{
	Super::NativeConstruct();

	BindUIEvents();
	
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->OnDeckUpdate.AddUObject(this, &UDeckDetailUI::RefreshTotalScore);
	}

}

void UDeckDetailUI::InitializeDetail(UDeckManager* Manager, const FDeckData& Data)
{
	
}

void UDeckDetailUI::OnDeckOwnerSelected( FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// String을 Enum으로 변환
	if (StringToEnumMap.Contains(SelectedItem))
	{
		SelectedDeckOwner = StringToEnumMap[SelectedItem];
		UE_LOG(LogTemp, Warning, TEXT("Selected DeckOwner: %s"), *SelectedItem);
	}
}

void UDeckDetailUI::InitializeDeckOwnerComboBox()
{
	if (!ComboBox_DeckOwner)
		return;

	// ComboBox 초기화
	ComboBox_DeckOwner->ClearOptions();

	// Enum의 모든 값을 순회하며 추가 -> 데이터베이스 플레이어 로 추후 변경
	const UEnum* EnumPtr = StaticEnum<EDeckOwner>();
    
	for (int32 i = 0; i < EnumPtr->NumEnums() - 1; ++i)  // -1은 MAX 값 제외
	{
		EDeckOwner EnumValue = static_cast<EDeckOwner>(EnumPtr->GetValueByIndex(i));
        
		// DisplayName 가져오기
		FString DisplayName = EnumPtr->GetDisplayNameTextByIndex(i).ToString();
        
		// ComboBox에 추가
		ComboBox_DeckOwner->AddOption(DisplayName);
        
		// 맵에 저장
		StringToEnumMap.Add(DisplayName, EnumValue);
		EnumToStringMap.Add(EnumValue, DisplayName);
	}

	// 기본값 설정
	SelectedDeckOwner = EDeckOwner::PLAYERA;
	ComboBox_DeckOwner->SetSelectedOption(EnumToStringMap[EDeckOwner::PLAYERA]);
	
}

void UDeckDetailUI::SetSelectedDeckOwner(EDeckOwner NewOwner)
{
	SelectedDeckOwner = NewOwner;
    
	if (ComboBox_DeckOwner && EnumToStringMap.Contains(NewOwner))
	{
		ComboBox_DeckOwner->SetSelectedOption(EnumToStringMap[NewOwner]);
	}
}

// 바인딩
void UDeckDetailUI::BindUIEvents()
{
	//콤보박스들
	if (ComboBox_DeckOwner== nullptr) return;
	ComboBox_DeckOwner->OnSelectionChanged.AddDynamic(this, &UDeckDetailUI::OnDeckOwnerSelected);
	
	//버튼들
	if (Button_DeckImage == nullptr) return;
	Button_DeckImage->OnClicked.AddDynamic(this, &UDeckDetailUI::OnChangeImage);
	
	if (Button_SaveButton == nullptr) return;
	Button_SaveButton->OnClicked.AddDynamic(this, &UDeckDetailUI::OnClickedSaveButton);
	
	if (Button_BackButton == nullptr) return;
	Button_BackButton->OnClicked.AddDynamic(this, &UDeckDetailUI::OnClickedBackButton);
	
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
void UDeckDetailUI::OnChangeImage()
{
	FButtonStyle btrStyle;
	FSlateBrush normal;
	FSlateBrush hover = normal;
	FSlateBrush pressed = normal;

	
	normal.ImageSize = FVector2D(695, 545);
	normal.TintColor = FSlateColor(FLinearColor::White);

	hover.ImageSize = FVector2D(695, 545);
	hover.TintColor = FSlateColor(FLinearColor(0.8f,0.8f,0.8f,1.0f));
	
	pressed.ImageSize = FVector2D(695, 545);
	pressed.TintColor = FSlateColor(FLinearColor(0.4f,0.4f,0.4f,1.0f));
	
	Button_DeckImage->SetStyle(btrStyle);
}

void UDeckDetailUI::OnClickedSaveButton()
{
	FString Error;
	
	FText Deployment =  Editable_Deployment->GetText();
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		//deckMgr->NotifyDeckListChanged();
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


void UDeckDetailUI::RefreshUI()
{
	if (Button_DeckImage == nullptr) return;;
	
	FButtonStyle btrStyle;
	FSlateBrush normal;// = DeckHelper->GetThumbnailBrush();
	FSlateBrush hover = normal;
	FSlateBrush pressed = normal;

	
	normal.ImageSize = FVector2D(695, 545);
	normal.TintColor = FSlateColor(FLinearColor::White);

	hover.ImageSize = FVector2D(695, 545);
	hover.TintColor = FSlateColor(FLinearColor(0.8f,0.8f,0.8f,1.0f));
	
	pressed.ImageSize = FVector2D(695, 545);
	pressed.TintColor = FSlateColor(FLinearColor(0.4f,0.4f,0.4f,1.0f));
	
	Button_DeckImage->SetStyle(btrStyle);
}

void UDeckDetailUI::UpdateStat(EDeckStatType StatType,float StatScore)
{
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		deckMgr->UpdateCurrentDeck(StatType,StatScore);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
}

void UDeckDetailUI::RefreshTotalScore()
{
	if (UDeckManager * deckMgr = GetWorld()->GetGameInstance()->GetSubsystem<UDeckManager>())
	{
		float totalScore = deckMgr->GetCurrentDeck().GetTotalScore();
		FString strFloat = FString::Printf(TEXT("%.2f"), totalScore);
		Text_TotalScore->SetText(FText::FromString(strFloat));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDeckManager is nullptr"));
	}
}

void UDeckDetailUI::OnCommentCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	//if (!DeckHelper) return;

	//DeckHelper->SetText(Text.ToString(),EEditableTextType::Comment);
}

void UDeckDetailUI::OnDeckNameCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	//if (!DeckHelper) return;

	//DeckHelper->SetText(Text.ToString(),EEditableTextType::DeckName);
}

void UDeckDetailUI::OnDeploymentValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float deploymentValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::DEPLOYMENT,deploymentValue);
}

void UDeckDetailUI::OnBreakthroughValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float breakthroghValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::BREAKTHROUGH,breakthroghValue);
}

void UDeckDetailUI::OnRetentionValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float retentionValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::RETENTION,retentionValue);
}

void UDeckDetailUI::OnRecoveryValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float recoveryValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::RECOVERY,recoveryValue);
}

void UDeckDetailUI::OnControlValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float controlValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::CONTROL,controlValue);
}

void UDeckDetailUI::OnFlexibilityValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float flexibilityValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::FLEXIBILITY,flexibilityValue);
}

void UDeckDetailUI::OnBasePowerValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float basePowerValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::BASEPOWER,basePowerValue);
}

void UDeckDetailUI::OnRelativeAValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float relativeAValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::RELATIVEA,relativeAValue);
}

void UDeckDetailUI::OnRelativeBValueCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	float relativeBValue =  FCString::Atof(*Text.ToString());
	UpdateStat(EDeckStatType::RELATIVEB,relativeBValue);
}

