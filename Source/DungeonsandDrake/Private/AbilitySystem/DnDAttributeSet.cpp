// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DnDAttributeSet.h"
#include "Net/UnrealNetwork.h"

UDnDAttributeSet::UDnDAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
}

void UDnDAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDnDAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDnDAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDnDAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDnDAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UDnDAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDnDAttributeSet, Health, OldHealth);
}

void UDnDAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDnDAttributeSet, MaxHealth, OldMaxHealth);
}

void UDnDAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDnDAttributeSet, Mana, OldMana);
}

void UDnDAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDnDAttributeSet, MaxMana, OldMaxMana);
}
