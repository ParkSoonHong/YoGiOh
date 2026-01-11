// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YoGiohPlayerController.generated.h"

class UInputAction;
class UUserWidget;
UCLASS()
class YOGIOH_API AYoGiohPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> Ui_Title;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Back;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Default;

	void OnBackPressed();

	
};
