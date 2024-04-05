// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DnDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighlightInterface;

UCLASS()
class DUNGEONSANDDRAKE_API ADnDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADnDPlayerController();

	virtual void AcknowledgePossession(class APawn* P) override;

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> DrakeContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	IHighlightInterface* CurrentActor;
	IHighlightInterface* LastActor;

	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();
};
