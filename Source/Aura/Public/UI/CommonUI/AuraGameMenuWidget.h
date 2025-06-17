// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonUI/AuraCommonActivatableWidget.h"
#include "AuraGameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameMenuWidget : public UAuraCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UAuraGameMenuWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UUserWidget interface
	virtual void NativeOnInitialized() override;
	//~End of UUserWidget interface

	//~UCommonActivatableWidget interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	//~End of UCommonActivatableWidget interface

protected:
	/** Callback called whenever the player gives the "Main Menu" input */
	void HandleGameMenuAction();


};
