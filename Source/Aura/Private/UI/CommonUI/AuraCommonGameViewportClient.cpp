// Copyright Kelly259


#include "UI/CommonUI/AuraCommonGameViewportClient.h"

#include "CommonUISettings.h"
#include "ICommonUIModule.h"

namespace GameViewportTags
{
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Platform_Trait_Input_HardwareCursor, "Platform.Trait.Input.HardwareCursor");
}

UAuraCommonGameViewportClient::UAuraCommonGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAuraCommonGameViewportClient::Init(FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);

	// We have software cursors set up in our project settings for console/mobile use, but on desktop
	// native hardware cursors are preferred.
	const bool bUseHardwareCursor = ICommonUIModule::GetSettings().GetPlatformTraits().HasTag(GameViewportTags::TAG_Platform_Trait_Input_HardwareCursor);
	SetUseSoftwareCursorWidgets(!bUseHardwareCursor);
}
