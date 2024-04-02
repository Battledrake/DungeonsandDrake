#include "Character/DnDCharacterBase.h"

ADnDCharacterBase::ADnDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StaticWeapon = CreateDefaultSubobject<UStaticMeshComponent>("StaticWeapon");
	StaticWeapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	StaticWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADnDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

