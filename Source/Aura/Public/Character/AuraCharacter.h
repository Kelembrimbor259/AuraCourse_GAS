// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//~ Combat Interface
	virtual int32 GetCharacterLevel() override;
	//~ Combat Interface
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* Camera;

private:

	virtual void InitAbilityActorInfo() override;
};
