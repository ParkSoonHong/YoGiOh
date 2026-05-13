// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Controller/YoGiohPlayerController.h"
#include "System/Popup/Manager/UiPopUpManager.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"

void AYoGiohPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	Initialize();
	
	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	}
	
	UUserWidget* TitleWidget = CreateWidget<UUserWidget>(GetWorld(), Ui_Title);
	
	if (TitleWidget)
	{
		TitleWidget->AddToViewport();
	}
}

void AYoGiohPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedIC =
		Cast<UEnhancedInputComponent>(InputComponent);

	if (!EnhancedIC)
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent missing"));
		return;
	}

	EnhancedIC->BindAction(
		IA_Back,
		ETriggerEvent::Triggered,
		this,
		&AYoGiohPlayerController::OnBackPressed
	);

}

void AYoGiohPlayerController::OnBackPressed()
{
	if (UUiPopUpManager* UIManager =
		GetWorld()->GetGameInstance()->GetSubsystem<UUiPopUpManager>())
	{
		UIManager->BackInput();
	}
}

void AYoGiohPlayerController::Initialize()
{
	bShowMouseCursor = true;
}
