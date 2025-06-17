// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "AuraCommonActivatableWidget.generated.h"

/**
 * Input Modes that AuraCommonActivatableWidgets can activate
 */
UENUM(BlueprintType)
enum class EAuraWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

/**
 * Activatable Widget
 *
 * An activatable widget that optionally overrides the input mode when activated
 */
UCLASS(Abstract, Blueprintable, meta=(Category=Aura))
class AURA_API UAuraCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UAuraCommonActivatableWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End of UCommonActivatableWidget interface
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category=Input)
	EAuraWidgetInputMode InputMode = EAuraWidgetInputMode::Default;
};
