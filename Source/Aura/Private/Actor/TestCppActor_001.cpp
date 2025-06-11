// Copyright Kelly259


#include "Actor/TestCppActor_001.h"

#include "GameplayTagContainer.h"
#include "Aura/AuraGameplayTags.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Messages/TestMessage.h"

// Sets default values
ATestCppActor_001::ATestCppActor_001()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.TickInterval = 5.f;
}

// Called when the game starts or when spawned
void ATestCppActor_001::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ATestCppActor_001::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MessagesCount++;
	
	// Message Tag for broadcast
	// Not needed, because GameplayTag can be specified directly inside BroadcastMessage
	FGameplayTag MessageTag = AuraTag::Message_Update_Health;
	
	// Create message to broadcast
	FTestMessageStruct TestMessage;
	TestMessage.MessageText = FString("This is a test message from C++");
	TestMessage.MessageCount = MessagesCount;

	//Broadcast the message
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage(MessageTag, TestMessage);
	
}

