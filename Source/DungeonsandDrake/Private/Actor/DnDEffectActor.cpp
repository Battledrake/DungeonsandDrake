#include "Actor/DnDEffectActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/DnDAttributeSet.h"
#include "DungeonsandDrake/DungeonsandDrake.h"
#include "AbilitySystemBlueprintLibrary.h"

ADnDEffectActor::ADnDEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(GetRootComponent());

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void ADnDEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	////HACK: Temporary workaround before GameplayEffect implementation.
	//if (IAbilitySystemInterface* AbilityActor = Cast<IAbilitySystemInterface>(OtherActor))
	//{
	//	const UDnDAttributeSet* DnDAttributeSet = Cast<UDnDAttributeSet>(AbilityActor->GetAbilitySystemComponent()->GetAttributeSet(UDnDAttributeSet::StaticClass()));

	//	UDnDAttributeSet* MutableDnDAttributeSet = const_cast<UDnDAttributeSet*>(DnDAttributeSet);
	//	MutableDnDAttributeSet->SetHealth(DnDAttributeSet->GetHealth() + 25.f);
	//	MutableDnDAttributeSet->SetMana(DnDAttributeSet->GetMana() + 20.f);
	//	Destroy();
	//}
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

void ADnDEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		check(GameplayEffectClass);

		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void ADnDEffectActor::HighlightActor()
{
	Mesh->SetRenderCustomDepth(true);
	Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
}

void ADnDEffectActor::UnHighlightActor()
{
	Mesh->SetRenderCustomDepth(false);
}
