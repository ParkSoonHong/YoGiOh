
#include "Title/UI/TitleUI.h"
#include "Components/Button.h"

void UTitleUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_DeckList)
	{
		Button_DeckList->OnClicked.AddDynamic(this, &UTitleUI::OnDeckListButtonClicked);
	}

	if (Button_Dual)
	{
		Button_Dual->OnClicked.AddDynamic(this, &UTitleUI::OnDualButtonClicked);
	}

	if (Button_Roll)
	{
		Button_Roll->OnClicked.AddDynamic(this, &UTitleUI::OnRollButtonClicked);
	}
}

void UTitleUI::OnDeckListButtonClicked()
{
	// 팝업 매니저에게 덱 리스트 팝업을 열라고 요청
}

void UTitleUI::OnDualButtonClicked()
{
	// 팝업 매니저에게 듀얼 팝업을 열라고 요청
}

void UTitleUI::OnRollButtonClicked()
{
	// 팝업 매니저에게 롤 팝업을 열라고 요청
}
