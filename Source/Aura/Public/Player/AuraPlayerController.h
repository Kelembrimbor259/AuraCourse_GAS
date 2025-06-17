// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "EnhancedInputComponent.h"
#include "GameplayTags.h"
#include "InputTriggers.h"
#include "InputActionValue.h"
#include "AuraPlayerController.generated.h"



// Forward declaring
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAuraInputActionMap;
struct FGameplayTag;
struct FEnhancedInputActionEventBinding;

class AAuraEnemy;

/**
 * Aura Player Controller
 */
UCLASS()
class AURA_API AAuraPlayerController : public ACommonPlayerController /** CommonGame base */
{
	GENERATED_BODY()

public:
	AAuraPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PlayerTick(float DeltaTime) override;
	
	AAuraEnemy* GetCurrentHoveredEnemy() const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupInputComponent() override;

	/** Array of IMC to use while this Pawn is possessed */
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<const UInputMappingContext>> InputMappingContexts;
	/** Map of InputActions to C++ GameplayTags */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<const UAuraInputActionMap> InputActionMap;
	
private:

	template<class UserClass, typename... VarTypes>
	void BindInputValueAction(UEnhancedInputComponent* EnhancedInputComponent, FGameplayTag InputTag, ETriggerEvent TriggerEvent, UserClass* Object, typename FEnhancedInputActionHandlerValueSignature::template TMethodPtr< UserClass, VarTypes... > Func, bool bLogIfNotFound, VarTypes... Vars);

	void Input_Move(const FInputActionValue& InputActionValue);
	
	TObjectPtr<AAuraEnemy> CurrentHoveredEnemy;

	UPROPERTY(Transient, VisibleInstanceOnly)
	TSet<int32> InputEventBindingHandles;
	
};

