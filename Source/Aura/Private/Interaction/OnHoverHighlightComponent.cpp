// Copyright Kelly259


#include "Interaction/OnHoverHighlightComponent.h"

UOnHoverHighlightComponent::UOnHoverHighlightComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;
}


void UOnHoverHighlightComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningActor = GetOwner<AActor>();
	if(!IsValid(OwningActor))
	{
		return;
	}

	OwningActor->OnBeginCursorOver.AddUniqueDynamic(this, &ThisClass::OnBeginCursorOver);
	OwningActor->OnEndCursorOver.AddUniqueDynamic(this, &ThisClass::OnEndCursorOver);
}

void UOnHoverHighlightComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(!IsValid(OwningActor))
	{
		return;
	}
 
	OwningActor->OnBeginCursorOver.Clear();
	OwningActor->OnEndCursorOver.Clear();
}

void UOnHoverHighlightComponent::OnBeginCursorOver(AActor* TouchedActor)
{
	if(!IsValid(TouchedActor))
	{
		return;
	}
 
	auto SkeletalMeshes(TouchedActor->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), MeshTag));
	for (auto* It : SkeletalMeshes)
	{
		if(!IsValid(It)) continue;
 
		auto* SkeletalMesh = Cast<USkeletalMeshComponent>(It);
		if(!IsValid(SkeletalMesh)) continue;
 
		SkeletalMesh->SetRenderCustomDepth(true);
	}
}

void UOnHoverHighlightComponent::OnEndCursorOver(AActor* TouchedActor)
{
	if(!IsValid(TouchedActor))
	{
		return;
	}
 
	auto SkeletalMeshes(TouchedActor->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), MeshTag));
	for (auto* It : SkeletalMeshes)
	{
		if(!IsValid(It)) continue;
 
		auto* SkeletalMesh = Cast<USkeletalMeshComponent>(It);
		if(!IsValid(SkeletalMesh)) continue;
 
		SkeletalMesh->SetRenderCustomDepth(false);
	}
}


