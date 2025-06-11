// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OnHoverHighlightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AURA_API UOnHoverHighlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOnHoverHighlightComponent();

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginCursorOver(AActor* TouchedActor);
 
	UFUNCTION()
	void OnEndCursorOver(AActor* TouchedActor);
 
	/** All the meshes on your character that have this tag will be highlighted */
	UPROPERTY(EditAnywhere, Category = "Highlight Settings")
	FName MeshTag;
	
public:	
	/** Cached owner of the component */
    UPROPERTY(Transient)
    AActor* OwningActor = nullptr;
		
};
