// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "AuraCommonActivatableWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
