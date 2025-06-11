// Copyright Kelly259


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/AuraGameplayTags.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Messages/WidgetMessages.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	SendAttributeMessage(AuraAttributeSet->GetHealth(), AuraTag::Message_Update_Health);
	SendAttributeMessage(AuraAttributeSet->GetMaxHealth(), AuraTag::Message_Update_MaxHealth);
	SendAttributeMessage(AuraAttributeSet->GetMana(), AuraTag::Message_Update_Mana);
	SendAttributeMessage(AuraAttributeSet->GetMaxMana(), AuraTag::Message_Update_MaxMana);
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

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

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			if (Tag.MatchesTag(AuraTag::Message_Effects))
			{
				//~ Debugging
				//const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				//GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, Msg);
				
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				SendWidgetRowMessage(Row);
			}
		}
	}
	);
}

void UOverlayWidgetController::SendAttributeMessage(const float& AttributeValue, const FGameplayTag& MessageTag) const
{
	// Assigning Message Tag for broadcast
	const FGameplayTag MsgTag = MessageTag;
	
	// Create message to broadcast
	FAttributeUpdate AttributeMessage;
	AttributeMessage.AttributeValue = AttributeValue;

	// Broadcast the message
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage(MsgTag, AttributeMessage);
	}

void UOverlayWidgetController::SendWidgetRowMessage(const FUIWidgetRow* WidgetRow) const
{
	const FGameplayTag MsgTag = AuraTag::Message_Effects;
	
	FSendWidgetEffectRow WidgetRowMessage;
	WidgetRowMessage.Row = *WidgetRow;

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage(MsgTag, WidgetRowMessage);
}



