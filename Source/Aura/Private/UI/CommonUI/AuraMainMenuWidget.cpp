// Copyright Kelly259


#include "UI/CommonUI/AuraMainMenuWidget.h"

#include "Aura/AuraGameplayTags.h"
#include "CommonUIExtensions.h"
#include "Input/CommonUIInputTypes.h"

UAuraMainMenuWidget::UAuraMainMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAuraMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// This registers a "UI Action Binding" with CommonUI, such that when the UI_Action_MainMenu UI Action occurs,
	// the delegate is called which forwards the event to our own HandleMainMenuAction
	constexpr bool bShouldDisplayInActionBar = false;
	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(AuraTag::UI_Action_MainMenu), bShouldDisplayInActionBar, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleMainMenuAction)));
}

void UAuraMainMenuWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	BlankGameWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), AuraTag::UI_Layer_Game, BlankWidgetClass);
	BlankGameMenuWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), AuraTag::UI_Layer_GameMenu, BlankWidgetClass);
}

void UAuraMainMenuWidget::NativeOnDeactivated()
{
	if (BlankGameWidget.IsValid())
	{
		UCommonUIExtensions::PopContentFromLayer(BlankGameWidget.Get());
		BlankGameWidget.Reset();
	}

	if (BlankGameMenuWidget.IsValid())
	{
		UCommonUIExtensions::PopContentFromLayer(BlankGameMenuWidget.Get());
		BlankGameMenuWidget.Reset();
	}
	
	Super::NativeOnDeactivated();
}

void UAuraMainMenuWidget::HandleMainMenuAction()
{
	// When the player gives a "main menu" action while the main menu is open,
	// it means we need to close the main menu and return to game.
	DeactivateWidget();
}
