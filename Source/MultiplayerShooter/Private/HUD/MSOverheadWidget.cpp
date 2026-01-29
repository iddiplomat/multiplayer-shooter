#include "HUD/MSOverheadWidget.h"

#include "Components/TextBlock.h"

void UMSOverheadWidget::SetDisplayText(const FString& TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UMSOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;

	switch (RemoteRole)
	{
	case ROLE_Authority:
		Role = FString("Authority");
		break;
	case ROLE_AutonomousProxy: 
		Role = FString("Autonomous Proxy");
		break;
	case ROLE_SimulatedProxy: 
		Role = FString("Simulated Proxy");
		break;
	default: 
		Role = FString("None");
		break;
	}
	
	FString RemoteRoleStr = FString::Printf(TEXT("Local Role: %s"), *Role);
	SetDisplayText(RemoteRoleStr);
}

void UMSOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}
