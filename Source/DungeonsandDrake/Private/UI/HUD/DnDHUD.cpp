// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DnDHUD.h"
#include "UI/Widget/DnDUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ADnDHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void ADnDHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_DnDHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overaly Widget Controller Class uninitialized, please fill out BP_DnDHUD"));

	OverlayWidget = CreateWidget<UDnDUserWidget>(GetWorld(), OverlayWidgetClass);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	OverlayWidget->AddToViewport();
}
