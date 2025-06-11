// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestCppActor_001.generated.h"

UCLASS()
class AURA_API ATestCppActor_001 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestCppActor_001();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MessagesCount = 0;
};
