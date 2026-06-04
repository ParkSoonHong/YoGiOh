
#include "Title/UI/TitleUI.h"

#include "System/Popup/Manager/UiPopUpManager.h"

#include "Components/Button.h"
#include "Deck/Manager/DeckManager.h"
#include "User/Manager/UserManager.h"


void UTitleUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_DeckList)
		Button_DeckList->OnClicked.AddDynamic(this, &UTitleUI::OnDeckListButtonClicked);

	if (Button_Calculator)
		Button_Calculator->OnClicked.AddDynamic(this, &UTitleUI::OnCalculatorButtonClicked);

	if (Button_RollManual)
		Button_RollManual->OnClicked.AddDynamic(this, &UTitleUI::OnRollManualButtonClicked);
	
	if (Button_AddUser)
		Button_AddUser->OnClicked.AddDynamic(this, &UTitleUI::OnAddUserButtonClicked);
}

void UTitleUI::OnAddUserButtonClicked()
{
	if (UUiPopUpManager* PopupManager = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupManager->PushPopup(EUIPopUpType::USERPROFILE);
	}
	
	if (UUserManager* userMgr = GetWorld()->GetGameInstance()->GetSubsystem<UUserManager>())
	{
		userMgr->CreateUserDomain();
	}
}

void UTitleUI::OnDeckListButtonClicked()
{
	if (UUiPopUpManager* PopupManager = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupManager->PushPopup(EUIPopUpType::TIERLIST);
	}
}

void UTitleUI::OnCalculatorButtonClicked()
{
	if (UUiPopUpManager* PopupManager = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupManager->PushPopup(EUIPopUpType::CALCCULATOR);
	}
}

void UTitleUI::OnRollManualButtonClicked()
{
	if (UUiPopUpManager* PopupManager = GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		PopupManager->PushPopup(EUIPopUpType::MANUAL);
	}
}
