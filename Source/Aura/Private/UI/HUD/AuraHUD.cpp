// Copyright Kelly259


#include "UI/HUD/AuraHUD.h"

#include "CommonActionWidget.h"
#include "UI/CommonUI/AuraCommonActivatableWidget.h"
//#include "UI/Widget/AuraUserWidget.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"))
	
	UCommonActivatableWidget* Widget = CreateWidget<UCommonActivatableWidget>(GetOwningPlayerController(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraCommonActivatableWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	// Delaying broadcasting initial values to next tick to make sure MID is set and ready to accept value changes
	FFunctionGraphTask::CreateAndDispatchWhenReady([WidgetController]()
	{
		// Ваш код здесь
		WidgetController->BroadcastInitialValues();
	}, TStatId(), nullptr, ENamedThreads::GameThread);
	
	
	Widget->AddToViewport();
	//Widget->ActivateWidget();
}

