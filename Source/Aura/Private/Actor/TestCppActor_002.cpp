// Copyright Kelly259


#include "Actor/TestCppActor_002.h"

#include "Aura/AuraGameplayTags.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Messages/TestMessage.h"

// Sets default values
ATestCppActor_002::ATestCppActor_002()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestCppActor_002::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	ListenerHandle = MessageSubsystem.RegisterListener(AuraTag::Message_Update_Health, this, &ThisClass::OnTestMessageReceived);
}

void ATestCppActor_002::OnTestMessageReceived(FGameplayTag Channel, const FTestMessageStruct& Payload)
{
	UE_LOG(LogTemp, Display, TEXT("%s. It is message number %d"), *Payload.MessageText, Payload.MessageCount);
}

// Called every frame
void ATestCppActor_002::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

