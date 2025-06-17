// Copyright Kelly259


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Aura/AuraGameplayTags.h"
#include "Character/AuraEnemy.h"
#include "InputMappingContext.h"
#include "Player/AuraInputConfig.h"

AAuraPlayerController::AAuraPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	bReplicates = true;
	bEnableMouseOverEvents = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CurrentHoveredEnemy = IsValid(CurrentClickablePrimitive.Get()) ?
		CurrentClickablePrimitive.Get()->GetOwner<AAuraEnemy>() : nullptr;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Add EnhancedInput IMCs
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();

		// Apply the array of IMCs in descending priority
		int32 Priority = InputMappingContexts.Num();
		for (const TObjectPtr<const UInputMappingContext>& Imc : InputMappingContexts)
		{
			// Don't store empty IMCs in Data Assets!
			if (ensure(Imc != nullptr))
			{
				FModifyContextOptions Options = {};
				Options.bIgnoreAllPressedKeysUntilRelease = false;

				Subsystem->AddMappingContext(Imc, Priority, Options);
				Priority--;
			}
		}
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	if (ensure(EnhancedInput))
	{
		constexpr bool bLogNotFound = true;

		BindInputValueAction(EnhancedInput, AuraTag::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, bLogNotFound);
		
	}
	
}

template <class UserClass, typename ... VarTypes>
void AAuraPlayerController::BindInputValueAction(UEnhancedInputComponent* EnhancedInputComponent, FGameplayTag InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FEnhancedInputActionHandlerValueSignature::TMethodPtr<UserClass, VarTypes...> Func, bool bLogIfNotFound, VarTypes... Vars)
{
	// The pawn **MUST** have an InputActionMap configured so we can map input actions to gameplay tags
	if (ensure(InputActionMap))
	{
		if (const UInputAction* Action = InputActionMap->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
		{
			const FEnhancedInputActionEventBinding& Binding = EnhancedInputComponent->BindAction(Action, TriggerEvent, Object, Func, Vars...);
			InputEventBindingHandles.Add(Binding.GetHandle());

		}
	}
}



void AAuraPlayerController::Input_Move(const FInputActionValue& InputActionValue)
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

AAuraEnemy* AAuraPlayerController::GetCurrentHoveredEnemy() const
{
	return CurrentHoveredEnemy;
}