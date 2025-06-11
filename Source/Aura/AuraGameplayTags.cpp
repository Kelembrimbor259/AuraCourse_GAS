// Copyright Kelly259

#include "AuraGameplayTags.h"

namespace AuraTag
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Update_Health,"Message.Update.Health", "Message to update Health");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Update_Mana,"Message.Update.Mana", "Message to update Mana");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Update_MaxHealth,"Message.Update.MaxHealth", "Message to update MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Update_MaxMana,"Message.Update.MaxMana", "Message to update MaxMana");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Update_Attribute,"Attributes.Update.Attribute", "Message to update some Attribute");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Send_EffectActorTags,"Message.Send.EffectActorTags", "Message with GameplayTagContainer of EffectActor");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Effects,"Message.Effects", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Effects_HealthPotion,"Message.Effects.HealthPotion", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Effects_ManaPotion,"Message.Effects.ManaPotion", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Effects_HealthCrystal,"Message.Effects.HealthCrystal", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Effects_ManaCrystal,"Message.Effects.ManaCrystal", "");
}