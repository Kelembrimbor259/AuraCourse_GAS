// Copyright Kelly259


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/AuraGameplayTags.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Messages/WidgetMessages.h"


UOverlayWidgetController::UOverlayWidgetController()
{
	AuraAbilitySystemComponent = nullptr;
	AuraAttributeSet = nullptr;
	
	
	
}

void UOverlayWidgetController::BroadcastInitialValues(UAuraAbilitySystemComponent* InASC)
{
	Super::BroadcastInitialValues(InASC);

	//~From Lyra
	AbilitySystemComponent = InASC;
	AuraAttributeSet = AbilitySystemComponent->GetSet<UAuraAttributeSet>();
	
	// Register to listen for attribute changes.
	AuraAttributeSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleHealthChanged);
	AuraAttributeSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	AuraAttributeSet->OnManaChanged.AddUObject(this, &ThisClass::HandleManaChanged);
	AuraAttributeSet->OnMaxManaChanged.AddUObject(this, &ThisClass::HandleMaxManaChanged);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth(), AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth(), AuraAttributeSet->GetMaxHealth());
	//~From Lyra
	
	//const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	

	// Not in use
#pragma region Broadcast initial values of attributes via delegates
	/*
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	*/
#pragma endregion
	
	SendAttributeMessage(AuraAttributeSet->GetHealth(), AuraTag::Message_Update_Health);
	SendAttributeMessage(AuraAttributeSet->GetMaxHealth(), AuraTag::Message_Update_MaxHealth);
	SendAttributeMessage(AuraAttributeSet->GetMana(), AuraTag::Message_Update_Mana);
	SendAttributeMessage(AuraAttributeSet->GetMaxMana(), AuraTag::Message_Update_MaxMana);
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	//const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	//Delegates with AddLambda()
#pragma region Delegates with AddLambda()
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			SendAttributeMessage(Data.NewValue, AuraTag::Message_Update_Health);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			SendAttributeMessage(Data.NewValue, AuraTag::Message_Update_MaxHealth);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			SendAttributeMessage(Data.NewValue, AuraTag::Message_Update_Mana);
		});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			SendAttributeMessage(Data.NewValue, AuraTag::Message_Update_MaxMana);
		});
#pragma endregion
	
	//Not in use
#pragma region Delegates with AddUobject()
	/*
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
		*/
#pragma endregion

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			if (Tag.MatchesTag(AuraTag::Message_Effects))
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, Msg);
				
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				//MessageWidgetRowDelegate.Broadcast(*Row);
				SendWidgetRowMessage(Row);
			}
		}
	}
	);
}
// Not in use
#pragma region UObject delegate bindings
/*
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	//OnHealthChanged.Broadcast(Data.NewValue);
	SendAttributeMessage(Data.NewValue, AuraTag::Message_Update_Health);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	//OnMaxHealthChanged.Broadcast(Data.NewValue);
	SendAttributeMessage(Data.NewValue, AuraTag::Message_Update_MaxHealth);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	//OnManaChanged.Broadcast(Data.NewValue);
	SendAttributeMessage(Data.NewValue, AuraTag::Message_Update_Mana);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	//OnMaxManaChanged.Broadcast(Data.NewValue);
	SendAttributeMessage(Data.NewValue, AuraTag::Message_Update_MaxMana);
}
*/
#pragma endregion

void UOverlayWidgetController::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnHealthChanged.Broadcast(OldValue, NewValue);
}

void UOverlayWidgetController::HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxHealthChanged.Broadcast(OldValue, NewValue);
}

void UOverlayWidgetController::HandleManaChanged(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnManaChanged.Broadcast(OldValue, NewValue);
}

void UOverlayWidgetController::HandleMaxManaChanged(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxManaChanged.Broadcast(OldValue, NewValue);
}

void UOverlayWidgetController::SendAttributeMessage(const float& AttributeValue, const FGameplayTag& MessageTag) const
{
	// Message Tag for broadcast
	// Not needed, because GameplayTag can be specified directly inside BroadcastMessage
	//FGameplayTag MessageTag = AuraTag::Attributes_Update_Attribute;
	
	// Create message to broadcast
	FAttributeUpdate AttributeMessage;
	AttributeMessage.AttributeValue = AttributeValue;

	// Broadcast the message
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage(MessageTag, AttributeMessage);
	}

void UOverlayWidgetController::SendWidgetRowMessage(const FUIWidgetRow* WidgetRow) const
{
	FSendWidgetEffectRow WidgetRowMessage;
	WidgetRowMessage.Row = *WidgetRow;

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage(AuraTag::Message_Effects, WidgetRowMessage);
}



