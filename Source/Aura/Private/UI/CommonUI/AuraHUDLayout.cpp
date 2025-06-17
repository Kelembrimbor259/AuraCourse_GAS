// Copyright Kelly259


#include "UI/CommonUI/AuraHUDLayout.h"

#include "CommonUIExtensions.h"
#include "Input/CommonUIInputTypes.h"
#include "Aura/AuraGameplayTags.h"

UAuraHUDLayout::UAuraHUDLayout(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAuraHUDLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// This registers a "UI Action Binding" with CommonUI, such that when the UI_Action_MainMenu UI Action occurs,
	// the delegate is called which forwards the event to our own HandleMainMenuAction
	constexpr bool bShouldDisplayInActionBar = false;
	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(AuraTag::UI_Action_MainMenu), bShouldDisplayInActionBar, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleMainMenuAction)));
}

void UAuraHUDLayout::HandleMainMenuAction()
{
	if (ensure(!MainMenuClass.IsNull()))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), AuraTag::UI_Layer_Menu, MainMenuClass);
	}
}
