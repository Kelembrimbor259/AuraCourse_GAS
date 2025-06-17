// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"
#include "AuraGameInstance.generated.h"

/**
 * CommonGame Game Instance
 *
 * Must be configured in DefaultEngine.ini:
 *
 * [/Script/EngineSettings.GameMapsSettings]
 * GameInstanceClass=/Script/XistCommonGameSample.XcgsGameInstance
 */
UCLASS()
class AURA_API UAuraGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

public:
	UAuraGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
