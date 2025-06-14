// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "CommonLocalPlayer.h"
#include "AuraCommonLocalPlayer.generated.h"

/**
 * CommonGame LocalPlayer
 *
 * Must be configured in DefaultEngine.ini:
 * 
 * [/Script/Engine.Engine]
 * LocalPlayerClassName=/Script/XistCommonGameSample.XcgsLocalPlayer
 */
UCLASS()
class AURA_API UAuraCommonLocalPlayer : public UCommonLocalPlayer
{
	GENERATED_BODY()

public:

	UAuraCommonLocalPlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
