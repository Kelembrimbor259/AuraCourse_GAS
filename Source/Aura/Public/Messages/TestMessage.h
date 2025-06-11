// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "TestMessage.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct AURA_API FTestMessageStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MessageText = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MessageCount = 0;
};