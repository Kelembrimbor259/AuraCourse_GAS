// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

class UAuraAbilitySystemComponent;

//~ Macros for attribute accessor functions
#pragma region Macros for attribute accessor functions
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/** GetHealthAttribute();
*	GetHealth() const;
*	SetHealth(float NewVal);
*	InitHealth(float NewVal); */
#pragma endregion Macros for attribute accessor functions
//~ Macros for attribute accessor functions


/**
 * Effect properties structure
 *
 * FGameplayEffectContextHandle EffectContextHandle
 * UAbilitySystemComponent* SourceASC
 * AActor* SourceAvatarActor
 * AController* SourceController
 * ACharacter* SourceCharacter
 * UAbilitySystemComponent* TargetASC
 * AActor* TargetAvatarActor
 * AController* TargetController
 * ACharacter* TargetCharacter
 */
USTRUCT()
struct FEffectProperties
{
	GENERATED_USTRUCT_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};




/**
 * Aura Gameplay Attribute Set
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent() const;
	
	// Required overriding function to register variables for replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	/*
	 * Vital Attributes
	 */
	
	//~ Creating Health and MaxHealth attributes
#pragma region Creating Health and MaxHealth attributes
	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "VitalAttributes|Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "VitalAttributes|Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
#pragma endregion  Creating Health and MaxHealth attributes
	//~ Creating Health and MaxHealth attributes

	//~ Creating Mana and MaxMana attribute
#pragma region Creating Mana and MaxMana attribute
	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "VitalAttributes|Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "VitalAttributes|Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
#pragma endregion  Creating Mana and MaxMana attributes
	//~ Creating Mana and MaxMana attribute

	//~ Test Stamina creation
#pragma region Stamina
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Stamina);
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Stamina, OldStamina);
	}
#pragma endregion Stamina
	//~ Test Stamina creation

	/*
	 * Primary Attributes
	 */

#pragma region Strength attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "PrimaryAttributes|Strength")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
	}
#pragma endregion Strength

#pragma region Intelligence attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "PrimaryAttributes|Intelligence")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
	}
#pragma endregion Intelligence attribute

#pragma region Resilience attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "PrimaryAttributes|Resilience")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
	}
	
#pragma endregion Resilience

#pragma region Vigor attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "PrimaryAttributes|Vigor")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
	}
#pragma endregion Vigor
	
protected:
	
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	// Used to track when the health and mana reaches 0.
	bool bOutOfHealth;
	bool bOutOfMana;

	// Store mana and health before any changes 
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;
	float MaxManaBeforeAttributeChange;
	float ManaBeforeAttributeChange;

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
