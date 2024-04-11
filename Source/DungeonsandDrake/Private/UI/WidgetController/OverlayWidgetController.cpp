// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/DnDAttributeSet.h"
#include "AbilitySystem/DnDAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UDnDAttributeSet* DnDAttributeSet = CastChecked<UDnDAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(DnDAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DnDAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(DnDAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(DnDAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UDnDAttributeSet* DnDAttributeSet = CastChecked<UDnDAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DnDAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DnDAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DnDAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DnDAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	Cast<UDnDAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Effect Tag: %s"), *Tag.ToString()));
		}
	});
}

void UOverlayWidgetController::AttributeValueChanged(const FOnAttributeChangeData& Data) const
{
	OnAttributeValueChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
