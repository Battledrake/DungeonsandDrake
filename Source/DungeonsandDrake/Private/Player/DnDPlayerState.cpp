// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DnDPlayerState.h"
#include "AbilitySystem/DnDAbilitySystemComponent.h"
#include "AbilitySystem/DnDAttributeSet.h"


ADnDPlayerState::ADnDPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDnDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDnDAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;


}
