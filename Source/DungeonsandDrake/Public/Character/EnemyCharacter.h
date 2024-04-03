// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DnDCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSANDDRAKE_API AEnemyCharacter : public ADnDCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()

	AEnemyCharacter();
	
public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

private:
	void SetCustomDepthStencil(UPrimitiveComponent* MeshComponent, bool bEnableCustomDepth, int32 StencilValue = 0);
};
