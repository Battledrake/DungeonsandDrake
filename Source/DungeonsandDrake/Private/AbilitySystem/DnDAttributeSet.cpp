// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DnDAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"

UDnDAttributeSet::UDnDAttributeSet()
{
	InitHealth(25.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
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

void UDnDAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UDnDAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC))
	{
		Props.SourceAvatarActor = Props.SourceASC->GetAvatarActor();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Props.SourceController->GetCharacter();
		}
	}


	if (AActor* TargetAvatarActor = Data.Target.GetAvatarActor())
	{
		Props.TargetAvatarActor = TargetAvatarActor;
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Props.TargetController->GetCharacter();
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UDnDAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);


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
