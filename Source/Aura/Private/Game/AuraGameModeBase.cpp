// Copyright Kelly259


#include "Game/AuraGameModeBase.h"



AAuraGameModeBase::AAuraGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//GameStateClass = AAuraGameState::StaticClass();
	//PlayerControllerClass = AAuraPlayerController::StaticClass();
	//DefaultPawnClass = AAuraPlayerCharacter::StaticClass();
	//HUDClass = AAuraHUD::StaticClass();
}

void AAuraGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AAuraGameModeBase::InitGameState()
{
	Super::InitGameState();
}
