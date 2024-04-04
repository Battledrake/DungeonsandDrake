// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DrakeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/DnDPlayerState.h"
#include "AbilitySystemComponent.h"

ADrakeCharacter::ADrakeCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ADrakeCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void ADrakeCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void ADrakeCharacter::InitAbilityActorInfo()
{
	ADnDPlayerState* DnDPlayerState = GetPlayerState<ADnDPlayerState>();
	check(DnDPlayerState);

	AbilitySystemComponent = DnDPlayerState->GetAbilitySystemComponent();
	AttributeSet = DnDPlayerState->GetAttributeSet();

	AbilitySystemComponent->InitAbilityActorInfo(DnDPlayerState, this);
}
