// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DnDCharacterBase.h"
#include "DrakeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSANDDRAKE_API ADrakeCharacter : public ADnDCharacterBase
{
	GENERATED_BODY()
	
public:
	ADrakeCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

private:
	virtual void InitAbilityActorInfo() override;
};
