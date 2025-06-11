// Copyright Kelly259


#include "AbilitySystem/Attributes/AuraAttributeSetBase.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAttributeSetBase)

class UWorld;

UAuraAttributeSetBase::UAuraAttributeSetBase()
{
}

UWorld* UAuraAttributeSetBase::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UAuraAbilitySystemComponent* UAuraAttributeSetBase::GetAuraAbilitySystemComponent() const
{
	return Cast<UAuraAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
