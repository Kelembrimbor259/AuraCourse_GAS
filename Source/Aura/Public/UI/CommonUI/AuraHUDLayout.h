// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonUI/AuraCommonActivatableWidget.h"
#include "AuraHUDLayout.generated.h"

/**
 * HUD Layout
 */
UCLASS(Abstract, BlueprintType, Blueprintable, meta=(DisplayName="Aura HUD Layout", Category=Xcgs))
class AURA_API UAuraHUDLayout : public UAuraCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UAuraHUDLayout(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UUserWidget interface
	virtual void NativeOnInitialized() override;
	//~End of UUserWidget interface

protected:
	
	/** Callback called whenever the player gives the "Show Main Menu" input */
	void HandleMainMenuAction();

	/** Class to use as the Main Menu for this HUD Layout */
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UAuraCommonActivatableWidget> MainMenuClass;

	/** Callback called whenever the player gives the "Show Main Menu" input */
	void HandleGameMenuAction();

	/** Class to use as the Main Menu for this HUD Layout */
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UAuraCommonActivatableWidget> GameMenuClass;
	
};
