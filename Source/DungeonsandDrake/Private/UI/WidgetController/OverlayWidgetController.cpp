// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/DnDAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UDnDAttributeSet* DnDAttributeSet = CastChecked<UDnDAttributeSet>(AttributeSet);

	OnAttributeValueChanged.Broadcast(DnDAttributeSet->GetHealth());
	OnAttributeValueChanged.Broadcast(DnDAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UDnDAttributeSet* DnDAttributeSet = CastChecked<UDnDAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DnDAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::AttributeValueChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DnDAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::AttributeValueChanged);
}

void UOverlayWidgetController::AttributeValueChanged(const FOnAttributeChangeData& Data) const
{
	OnAttributeValueChanged.Broadcast(Data.NewValue);
}
