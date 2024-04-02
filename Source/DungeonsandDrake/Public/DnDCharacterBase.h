

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DnDCharacterBase.generated.h"

UCLASS()
class DUNGEONSANDDRAKE_API ADnDCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADnDCharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


};
