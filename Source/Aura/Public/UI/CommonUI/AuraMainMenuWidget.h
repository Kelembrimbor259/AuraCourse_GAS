// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonUI/AuraCommonActivatableWidget.h"
#include "AuraMainMenuWidget.generated.h"

/**
 * Main Menu Widget
 *
 * An Activatable Widget that closes itself if/when the "Main Menu" input action
 * triggers while the widget is open.  Not useful for any widget other than a
 * Main Menu widget.
 *
 * This also explicitly pushes a blank widget onto the lower layers (Game and GameMenu)
 * so that any open UI elements cannot be interacted with at all while the main menu
 * is open.  Change how you prefer.
 */
UCLASS()
class AURA_API UAuraMainMenuWidget : public UAuraCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UAuraMainMenuWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UUserWidget interface
	virtual void NativeOnInitialized() override;
	//~End of UUserWidget interface

	//~UCommonActivatableWidget interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	//~End of UCommonActivatableWidget interface

protected:
	/** Callback called whenever the player gives the "Main Menu" input */
	void HandleMainMenuAction();

	/** Blank widget to "occlude" lower layer widgets while the main menu is active */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraCommonActivatableWidget> BlankWidgetClass;

private:
	UPROPERTY(Transient)
	TWeakObjectPtr<UCommonActivatableWidget> BlankGameWidget;

	UPROPERTY(Transient)
	TWeakObjectPtr<UCommonActivatableWidget> BlankGameMenuWidget;
};
