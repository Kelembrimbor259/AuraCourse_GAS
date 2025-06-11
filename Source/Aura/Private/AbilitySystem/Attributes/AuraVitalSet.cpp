// Copyright Kelly259


#include "AbilitySystem/Attributes/AuraVitalSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraVitalSet)

UAuraVitalSet::UAuraVitalSet()
	: Health(100.f)
	, MaxHealth(100.f)
	, Mana(100.f)
	, MaxMana(100.f)
{
	bOutOfHealth = false;
	HealthBeforeAttributeChange = 0.f;
	MaxHealthBeforeAttributeChange = 0.f;
	ManaBeforeAttributeChange = 0.f;
	MaxManaBeforeAttributeChange = 0.f;
}

void UAuraVitalSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//~ Marking Health attribute for replication
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraVitalSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraVitalSet, MaxHealth, COND_None, REPNOTIFY_Always);

	//~ Marking Mana attribute for replication
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraVitalSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraVitalSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraVitalSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraVitalSet, Health, OldValue);
}

void UAuraVitalSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraVitalSet, MaxHealth, OldValue);
}

void UAuraVitalSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraVitalSet, Mana, OldValue);
}

void UAuraVitalSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraVitalSet, MaxMana, OldValue);
}

bool UAuraVitalSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	//~ Save the current health
	HealthBeforeAttributeChange = GetHealth();
	MaxHealthBeforeAttributeChange = GetMaxHealth();

	return true;
}

void UAuraVitalSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectPropertiesStruct Props;
	SetEffectProperties(Data, Props);

	//float MinimumHealth = 0.0f;
	
}

void UAuraVitalSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UAuraVitalSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UAuraVitalSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		//~ Make sure current health is not greater than the new max health.
		if (GetHealth() > NewValue)
		{
			UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent();
			check(AuraASC);

			AuraASC->ApplyModToAttribute(GetHealthAttribute(), EGameplayModOp::Override, NewValue);
		}
	}
	if (Attribute == GetMaxManaAttribute())
	{
		//~ Make sure current health is not greater than the new max health.
		if (GetMana() > NewValue)
		{
			UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent();
			check(AuraASC);

			AuraASC->ApplyModToAttribute(GetManaAttribute(), EGameplayModOp::Override, NewValue);
		}
	}
}

void UAuraVitalSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		//~ Do not allow max health to drop below 1.
		NewValue = FMath::Max(NewValue, 1.0f);
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	if (Attribute == GetMaxManaAttribute())
	{
		//~ Do not allow max mana to drop below 1.
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}

void UAuraVitalSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectPropertiesStruct& Props) const
{
	//~ Source = causer  of the effect, Target = target of the effect (owner of this AS)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->GetAvatarActor();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
