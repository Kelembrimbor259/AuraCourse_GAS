// Copyright Kelly259


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"

#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	/**
	 * Line trace from cursor. There are several scenarious:
	 * A. LastActor is null && ThisActor is null
	 * - Do nothing
	 * B. LastActor is null && ThisActor is valid
	 * - Highlight ThisActor
	 * C. LastActor is valid && ThisActor is null
	 * - UnHighlight LastActor
	 * D. Both actors are valid, but LastActor != ThisActor
	 * - UnHighlight LastActor, Highlight ThisActor
	 * E. Both actors are valid, but LastActor = ThisActor
	 * - Do nothing
	 * **/


	if (LastActor.GetInterface()) //LastActor is valid
	{
		if (ThisActor.GetInterface()) // ThisActor is valid
		{
			if (LastActor.GetInterface() == ThisActor.GetInterface()) // Case E
			{
				
			}
			else // Case D
			{
				LastActor.GetInterface()->UnHighlightActor();
				ThisActor.GetInterface()->HighlightActor();
			}
		}
		else // Case C
		{
			LastActor.GetInterface()->UnHighlightActor();
		}
	}
	else //LastActor is null
	{
		if (ThisActor.GetInterface()) // Case B
		{
			ThisActor.GetInterface()->HighlightActor();
		}
		else // Case A
		{
			
		}
	}
		
	/*
	if (!LastActor.GetInterface())
	{
		if (ThisActor.GetInterface())
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A
		}
	}
	else // LastActor is valid
	{
		if (!ThisActor.GetInterface())
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else 
			{
				//Case E
			}
		}
	}
	*/
	
}
