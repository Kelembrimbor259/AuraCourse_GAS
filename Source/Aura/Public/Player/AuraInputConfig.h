﻿// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

class UInputAction;

/**
 * Input Action
 *
 * Struct used to map an Input Action to a Gameplay Tag
 */
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

public:
	/** The IA asset for this input */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	/** The GameplayTag unique to this Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * Input Action Map
 *
 * Const DataAsset that allows us to map IA_* assets (that C++ can't
 * easily work with) to GameplayTags (which it can).
 *
 * When EnhancedInput is handling input, it will have the InputAction available,
 * but it will then need to translate that to a GameplayTag so C++ can deal with it.
 * Thus each InputAction should be listed ONLY ONCE.
 */
UCLASS(BlueprintType, Const)
class AURA_API UAuraInputActionMap : public UDataAsset
{
	GENERATED_BODY()

public:
	UAuraInputActionMap(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:
	/**
	 * These input actions are mapped to a Gameplay Tag and must be manually bound
	 * via that Gameplay Tag in C++ to do whatever you want this input to do.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FAuraInputAction> NativeInputActions;
};
