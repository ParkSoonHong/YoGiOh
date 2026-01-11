// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Controller/YoGiohPlayerController.h"
#include "System/Popup/Manager/UiPopUpManager.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

void AYoGiohPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	}


	bShowMouseCursor = true;

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
