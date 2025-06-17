// Copyright Kelly259

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "AuraHUD.generated.h"

class UAuraCommonActivatableWidget;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
//class UAuraUserWidget;

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:

	AAuraHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	TObjectPtr<UAuraCommonActivatableWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:

	//~UObject interface
	virtual void PreInitializeComponents() override;
	//~End of UObject interface

	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraCommonActivatableWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
