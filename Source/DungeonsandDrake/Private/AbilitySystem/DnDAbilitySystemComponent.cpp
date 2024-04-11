// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DnDAbilitySystemComponent.h"

void UDnDAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDnDAbilitySystemComponent::EffectApplied);
}

void UDnDAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, FString("Effect Applied!"));
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

	//for (const FGameplayTag& Tag : TagContainer)
	//{
	//	//TODO: Broadcast the tag to the Widget Controller
	//	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Effect Tag: %s"), *Tag.ToString()));
	//}
}
