// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "CommonGameViewportClient.h"
#include "AuraCommonGameViewportClient.generated.h"

/**
 * CommonGame Game Viewport Client
 *
 * Must be configured in DefaultEngine.ini:
 * 
 * [/Script/Engine.Engine]
 * GameViewportClientClassName=/Script/XistCommonGameSample.XcgsGameViewportClient
 */

UCLASS()
class AURA_API UAuraCommonGameViewportClient : public UCommonGameViewportClient
{
	GENERATED_BODY()

public:
	UAuraCommonGameViewportClient(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UGameViewportClient interface
	virtual void Init(FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice) override;
	//~End of UGameViewportClient
};
