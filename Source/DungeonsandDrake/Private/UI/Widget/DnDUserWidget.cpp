// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/DnDUserWidget.h"

void UDnDUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
