// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DnDHUD.generated.h"

class UDnDUserWidget;

UCLASS()
class DUNGEONSANDDRAKE_API ADnDHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UDnDUserWidget> OverlayWidget;

protected:

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDnDUserWidget> OverlayWidgetClass;
};
