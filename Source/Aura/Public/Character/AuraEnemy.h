// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	//~ Combat Interface
	virtual int32 GetCharacterLevel() override;
	//~ Combat Interface

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 CharacterLevel = 1;

private:
	
	
	
	
	
};
