
#include "Title/UI/TitleUI.h"

#include "System/Popup/Manager/UiPopUpManager.h"

#include "Components/Button.h"


void UTitleUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_DeckList)
	{
		Button_DeckList->OnClicked.AddDynamic(this, &UTitleUI::OnDeckListButtonClicked);
	}

	if (Button_Calculator)
	{
		Button_Calculator->OnClicked.AddDynamic(this, &UTitleUI::OnCalculatorButtonClicked);
	}

	if (Button_RollManual)
	{
		Button_RollManual->OnClicked.AddDynamic(this, &UTitleUI::OnRollManualButtonClicked);
	}
}

void UTitleUI::OnDeckListButtonClicked()
{
	if (UUiPopUpManager* PopupManager = GetWorld()->
	   GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupManager->PushPopup(EUIPopUpType::TIERLIST);
	}
}

void UTitleUI::OnCalculatorButtonClicked()
{
	if (UUiPopUpManager* PopupManager = GetWorld()->
	   GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupManager->PushPopup(EUIPopUpType::CALCCULATOR);
	}
}

void UTitleUI::OnRollManualButtonClicked()
{
	if (UUiPopUpManager* PopupManager = GetWorld()->
	   GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupManager->PushPopup(EUIPopUpType::MANUAL);
	}
}
