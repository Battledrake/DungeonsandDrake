#include "Player/DnDPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/HighlightInterface.h"

ADnDPlayerController::ADnDPlayerController()
{
	bReplicates = true;
}

void ADnDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ADnDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(DrakeContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(DrakeContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ADnDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADnDPlayerController::Move);
}

void ADnDPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ADnDPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	if (GetHitResultUnderCursor(ECC_Camera, false, CursorHit))
	{
		LastActor = CurrentActor;
		CurrentActor = Cast<IHighlightInterface>(CursorHit.GetActor());

		if (CurrentActor != LastActor)
		{
			if (LastActor != nullptr)
			{
				LastActor->UnHighlightActor();
			}

			if (CurrentActor != nullptr)
			{
				CurrentActor->HighlightActor();
			}
		}

		/*
			A.	LastActor && CurrentActor == null
			 - DoNothing
		
			B. LastActor is null && CurrentActor is valid
			 - Highlight Current Actor

			C. LastActor is valid && CurrentActor is null
			 - Unhighlight LastActor

			D. LastActor is valid && CurrentActor is valid but !=
			 - Unhighlight LastActor. Highlight CurrentActor.

			E. Both valid. Actors ==
			 - Do Nothing
		*/
	}
}
