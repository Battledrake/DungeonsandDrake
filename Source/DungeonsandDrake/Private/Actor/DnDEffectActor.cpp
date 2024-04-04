#include "Actor/DnDEffectActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/DnDAttributeSet.h"

ADnDEffectActor::ADnDEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ADnDEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//HACK: Temporary workaround before GameplayEffect implementation.
	if (IAbilitySystemInterface* AbilityActor = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UDnDAttributeSet* DnDAttributeSet = Cast<UDnDAttributeSet>(AbilityActor->GetAbilitySystemComponent()->GetAttributeSet(UDnDAttributeSet::StaticClass()));

		UDnDAttributeSet* MutableDnDAttributeSet = const_cast<UDnDAttributeSet*>(DnDAttributeSet);
		MutableDnDAttributeSet->SetHealth(DnDAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ADnDEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ADnDEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADnDEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADnDEffectActor::EndOverlap);
}
