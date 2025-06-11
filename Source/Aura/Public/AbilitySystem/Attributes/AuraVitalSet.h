// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/AuraAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "AuraVitalSet.generated.h"


/**
 * UAuraVitalSet
 *
 * Class that defines vital attributes such as Health and Mana
 */
UCLASS()
class AURA_API UAuraVitalSet : public UAuraAttributeSetBase
{
	GENERATED_BODY()

	UAuraVitalSet();

public:
	
	//Creating attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "VitalAttributes|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "VitalAttributes|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "VitalAttributes|Mana", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "VitalAttributes|Mana", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;
	
	//Set attribute accessors
	ATTRIBUTE_ACCESSORS(UAuraVitalSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraVitalSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraVitalSet, Mana);
	ATTRIBUTE_ACCESSORS(UAuraVitalSet, MaxMana);

protected:
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	// Required overriding function to register variables for replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	
	// Used to track when the health reaches 0.
	bool bOutOfHealth;
	
	// Store the health and mana before any changes 
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;
	float MaxManaBeforeAttributeChange;
	float ManaBeforeAttributeChange;

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectPropertiesStruct& Props) const;
};
