// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DnDHUD.h"
#include "UI/Widget/DnDUserWidget.h"

void ADnDHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
