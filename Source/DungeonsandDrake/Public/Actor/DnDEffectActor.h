#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/HighlightInterface.h"
#include "DnDEffectActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DUNGEONSANDDRAKE_API ADnDEffectActor : public AActor, public IHighlightInterface
{
	GENERATED_BODY()
	
public:	
	ADnDEffectActor();

	//~ Begin Highlight Interface
	void HighlightActor() override;
	void UnHighlightActor() override;
	//~ End Highlight Interface

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

};
