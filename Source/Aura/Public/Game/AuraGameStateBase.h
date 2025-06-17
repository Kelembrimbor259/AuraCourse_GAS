// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "ModularGameState.h"
#include "AuraGameStateBase.generated.h"

/**
 * Modular Game State
 */
UCLASS(meta=(Category=Aura))
class AURA_API AAuraGameStateBase : public AModularGameStateBase
{
	GENERATED_BODY()

public:
	AAuraGameStateBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	
};
