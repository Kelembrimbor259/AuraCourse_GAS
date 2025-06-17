// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "AuraGameModeBase.generated.h"

/**
 * Modular Game Mode
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AModularGameModeBase
{
	GENERATED_BODY()

public:
	AAuraGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	//~End of AGameModeBase interface
	
};
