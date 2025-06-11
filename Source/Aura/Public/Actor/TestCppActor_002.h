// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "TestCppActor_002.generated.h"

struct FTestMessageStruct;
struct FGameplayTag;

UCLASS()
class AURA_API ATestCppActor_002 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestCppActor_002();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnTestMessageReceived(FGameplayTag Channel, const FTestMessageStruct& Payload);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FGameplayMessageListenerHandle ListenerHandle;

};
