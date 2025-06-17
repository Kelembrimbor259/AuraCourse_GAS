// Copyright Kelly259

#pragma once

#include "NativeGameplayTags.h"

namespace AuraTag
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Update_Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Update_Mana);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Update_MaxHealth);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Update_MaxMana);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Update_Attribute);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Send_EffectActorTags);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Effects);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Effects_HealthPotion);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Effects_ManaPotion);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Effects_HealthCrystal);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Effects_ManaCrystal);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Action_MainMenu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Game);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_GameMenu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Menu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Modal);
}