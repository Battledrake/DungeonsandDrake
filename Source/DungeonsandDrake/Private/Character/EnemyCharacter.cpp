// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "DungeonsandDrake/DungeonsandDrake.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AEnemyCharacter::HighlightActor()
{
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 50.f, 16, FColor::Red, true);

	SetCustomDepthStencil(GetMesh(), true, CUSTOM_DEPTH_RED);
	SetCustomDepthStencil(Weapon, true, CUSTOM_DEPTH_RED);
	SetCustomDepthStencil(StaticWeapon, true, CUSTOM_DEPTH_RED);
}

void AEnemyCharacter::UnHighlightActor()
{
	//UKismetSystemLibrary::FlushPersistentDebugLines(this);

	SetCustomDepthStencil(GetMesh(), false);
	SetCustomDepthStencil(Weapon, false);
	SetCustomDepthStencil(StaticWeapon, false);
}

void AEnemyCharacter::SetCustomDepthStencil(UPrimitiveComponent* MeshComponent, bool bEnableCustomDepth, int32 StencilValue)
{
	if (MeshComponent)
	{
		MeshComponent->SetRenderCustomDepth(bEnableCustomDepth);
		MeshComponent->SetCustomDepthStencilValue(StencilValue);
	}
}
