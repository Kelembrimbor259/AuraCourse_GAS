// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "AttributeUpdateMessage.generated.h"

/**
 * Message to broadcast on attribute updates to the widgets
 */

/*
USTRUCT(BlueprintType)
struct AURA_API FAttributeUpdate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttributeValue;
};
*/

USTRUCT(BlueprintType)
struct AURA_API FAttributeUpdateOld
{
	GENERATED_BODY()

public:
	FAttributeUpdateOld() : AttributeValue(0.0f) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttributeValue;
};