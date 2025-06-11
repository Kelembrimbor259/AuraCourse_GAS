// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "WidgetMessages.generated.h"

/**
 * Message to broadcast on attribute updates to the widgets
 */

USTRUCT(BlueprintType)
struct AURA_API FAttributeUpdate
{
	GENERATED_BODY()

public:
	FAttributeUpdate() : AttributeValue(0.0f) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttributeValue;
};

/**
 * 
 */

USTRUCT(BlueprintType)
struct AURA_API FSendWidgetEffectRow
{
	GENERATED_BODY()

public:
	FSendWidgetEffectRow() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUIWidgetRow Row;
};

