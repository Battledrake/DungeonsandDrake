

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DnDCharacterBase.generated.h"

UCLASS(Abstract)
class DUNGEONSANDDRAKE_API ADnDCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADnDCharacterBase();

protected:
	virtual void BeginPlay() override;

private:


};
