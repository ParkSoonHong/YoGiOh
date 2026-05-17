// Fill out your copyright notice in the Description page of Project Settings.


#include "TierList/UI/DeckDetailUI.h"
#include "Deck/Type//EDeckOwner.h"
//#include "System/Popup/UiPopUpManager.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Deck/Manager/DeckManager.h"
#include "TierList/UI/TierListUI.h"
#include "Deck/Manager/DeckManagerHelper.h"

void UDeckDetailUI::NativeConstruct()
{
	Super::NativeConstruct();

	
	if (Button_SaveButton)
	{
		Button_SaveButton->OnClicked.AddDynamic(this,&UDeckDetailUI::OnSave);
	}
//	DeckManager = GetWorld()->GetSubsystem<UDeckManager>();
	
	/*
	InitializeDeckOwnerComboBox();
	BindUIEvents();
	*/
}

void UDeckDetailUI::InitializeDetail(UDeckManager* Manager, const FDeckSaveData& Data)
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

	// Enum의 모든 값을 순회하며 추가
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
	SelectedDeckOwner = EDeckOwner::PlayerA;
	ComboBox_DeckOwner->SetSelectedOption(EnumToStringMap[EDeckOwner::PlayerA]);
	
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
	if (ComboBox_DeckOwner== nullptr) return;
	ComboBox_DeckOwner->OnSelectionChanged.AddDynamic(this, &UDeckDetailUI::OnDeckOwnerSelected);
	
	if (Button_DeckImage == nullptr) return;
	Button_DeckImage->OnClicked.AddDynamic(this, &UDeckDetailUI::OnChangeImage);
	
	if (Button_SaveButton == nullptr) return;
	Button_SaveButton->OnClicked.AddDynamic(this, &UDeckDetailUI::OnSave);
	
	if (Editable_Comment == nullptr) return;
	Editable_Comment->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnCommentCommitted);
	
	if (Editable_DeckName == nullptr) return;
	Editable_DeckName->OnTextCommitted.AddDynamic(this, &UDeckDetailUI::OnDeckNameCommitted);
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

void UDeckDetailUI::OnSave()
{
	FString Error;
	/*
	if (!DeckHelper->Save(Error))
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *Error);
		return;
	}
	*/
	UWorld * world =  GetWorld();
		
	UGameInstance * instance =  world->GetGameInstance();
		
	UDeckManager * deckManager = instance->GetSubsystem<UDeckManager>();
	deckManager->NotifyDeckListChanged();
		
	//UUiPopUpManager * popupManager = instance->GetSubsystem<UUiPopUpManager>();
	//popupManager->PopPopup();	
}


void UDeckDetailUI::RefreshUI()
{
	RefreshScore(); // 내부에서 호출
	
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

void UDeckDetailUI::RefreshScore()
{
	//Text_TotalScore->SetText(DeckHelper->GetTotalScoreText());

	/*
	Slider_Deployment->SetValue(Data.Deployment / 10.f);
	Text_Deployment->SetText(FText::AsNumber(Data.Deployment));
	
	Slider_Breakthrough->SetValue(Data.Breakthrough / 10.f);
	Text_Breakthrough->SetText(FText::AsNumber(Data.Breakthrough));
	
	Slider_Retention->SetValue(Data.Retention / 10.f);
	Text_Retention->SetText(FText::AsNumber(Data.Retention));
	
	Slider_Recovery->SetValue(Data.Recovery / 10.f);
	Text_Recovery->SetText(FText::AsNumber(Data.Recovery));
	
	Slider_Control->SetValue(Data.Control / 10.f);
	Text_Control->SetText(FText::AsNumber(Data.Control));
	
	Slider_Flexibility->SetValue(Data.Flexibility / 10.f);
	Text_Flexibility->SetText(FText::AsNumber(Data.Flexibility));
	
	Slider_BasePower->SetValue(Data.BasePower / 10.f);
	Text_BasePower->SetText(FText::AsNumber(Data.BasePower));
	
	Slider_RelativeA->SetValue(Data.RelativeA / 10.f);
	Text_RelativeA->SetText(FText::AsNumber(Data.RelativeA));
	
	Slider_RelativeB->SetValue(Data.RelativeB / 10.f);
	Text_RelativeB->SetText(FText::AsNumber(Data.RelativeB));
	*/
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
