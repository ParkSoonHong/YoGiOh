// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Popup/UiPopUpBase.h"
#include "Deck/Data/FDeckData.h"
#include "Deck/Domain/FDeckDomain.h"
#include "Deck/Type/EDeckRank.h"
#include "TierListUI.generated.h"

class UComboBoxString;
class UEditableText;
class UDeckManager;
class UTierSlotUI;
class UTierLineUI;
class UDeckSlotUI;
class UVerticalBox;
class UButton;

UCLASS()
class YOGIOH_API UTierListUI : public UUiPopUpBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox * VerticalBox_Tier;
	
	UPROPERTY(meta = (BindWidget))
	UButton * Button_DataAdd;
	UPROPERTY(meta = (BindWidget))
	UButton * Button_Back;
	UPROPERTY(meta = (BindWidget))
	UButton * Button_Search;
	
	UPROPERTY(meta = (BindWidget))
	UEditableText * EditableText_InsertText;
	UPROPERTY(meta = (BindWidget))
	UComboBoxString * ComboBoxString_Filter;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> SlotClass;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> LineClass;
	
	FDeckData PendingDetailData;

private:

	void BuildTierMap(const TArray<FDeckDomain>& Decks);
	void RefreshList(const TArray<FDeckDomain>& Decks);

	TMap<EDeckRank,TArray<FDeckDomain>> tierMap;
public:
	
	UFUNCTION()
	void OnClickedDataAddButton();
	
	UFUNCTION()
	void OnClickedBackButton();
	
	UFUNCTION()
	void OnClickedSearchButton();
	
	UFUNCTION()
	void OnFilterSelected( FString SelectedItem, ESelectInfo::Type SelectionType);
	
	UFUNCTION()
	void OnInsertTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
