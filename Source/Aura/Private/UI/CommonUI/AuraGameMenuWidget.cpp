// Copyright Kelly259


#include "UI/CommonUI/AuraGameMenuWidget.h"

#include "Aura/AuraGameplayTags.h"
#include "CommonUIExtensions.h"
#include "Input/CommonUIInputTypes.h"

UAuraGameMenuWidget::UAuraGameMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAuraGameMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// This registers a "UI Action Binding" with CommonUI, such that when the UI_Action_MainMenu UI Action occurs,
	// the delegate is called which forwards the event to our own HandleMainMenuAction
	constexpr bool bShouldDisplayInActionBar = false;
	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(AuraTag::UI_Action_GameMenu), bShouldDisplayInActionBar, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleGameMenuAction)));
}

void UAuraGameMenuWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
}

void UAuraGameMenuWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
}

void UAuraGameMenuWidget::HandleGameMenuAction()
{
	// When the player gives a "main menu" action while the main menu is open,
	// it means we need to close the main menu and return to game.
	DeactivateWidget();
}
