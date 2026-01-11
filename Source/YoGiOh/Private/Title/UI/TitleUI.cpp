
#include "Title/UI/TitleUI.h"
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
	//OnRequestPush.Broadcast(EUIPopUpType::TierList);
}

void UTitleUI::OnCalculatorButtonClicked()
{
	//OnRequestPush.Broadcast(EUIPopUpType::Calculator);
}

void UTitleUI::OnRollManualButtonClicked()
{
	//OnRequestPush.Broadcast(EUIPopUpType::Manual);
}
