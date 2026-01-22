#include "Menu.h"

#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Online/OnlineSessionNames.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LobbyPath)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath);
	
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);
	
	UWorld* World = GetWorld();
	if (!World) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;
	
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(true);
	
	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance) return;
	
	MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	if (!MultiplayerSessionsSubsystem) return;
	
	MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &UMenu::OnCreateSession);
	MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &UMenu::OnFindSession);
	MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &UMenu::OnJoinSession);
	MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &UMenu::OnDestroySession);
	MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &UMenu::OnStartSession);
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
	}
	
	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();
 
	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Session created!"));
		}
		
		UWorld* World = GetWorld();
		if (!World)	return;
	
		World->ServerTravel(PathToLobby);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Failed to create session!"));
		}	
	}
}

void UMenu::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (!MultiplayerSessionsSubsystem)
	{
		return;
	}
	
	for (FOnlineSessionSearchResult Result : SessionResults)
	{
		const FString Id = Result.GetSessionIdStr();
		const FString User = Result.Session.OwningUserName;
		FString SettingsValue;
		
		// TODO::Search for better fix for that part!
		Result.Session.SessionSettings.bUsesPresence = true;
		Result.Session.SessionSettings.bUseLobbiesIfAvailable = true;
		
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		
		if (SettingsValue == MatchType)
		{
			MultiplayerSessionsSubsystem->JoinSession(Result);
			return;
		}
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (!MultiplayerSessionsSubsystem)
	{
		return;
	}
	
	if (!MultiplayerSessionsSubsystem->GetSessionInterface().IsValid())
	{
		return;
	}
	
	if (GEngine)
	{
		if (Result != EOnJoinSessionCompleteResult::Success)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Failed to join session!"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Joined session!"));
		}
	}
	
	FString ConnectInfo;
	MultiplayerSessionsSubsystem->GetSessionInterface()->GetResolvedConnectString(NAME_GameSession, ConnectInfo);
	
	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (!PlayerController)
	{
		return;
	}
	
	PlayerController->ClientTravel(ConnectInfo, TRAVEL_Absolute);
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
}

void UMenu::HostButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Host Button Clicked"));
	}
	
	if (!MultiplayerSessionsSubsystem) return;
	
	MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);
}

void UMenu::JoinButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->FindSessions(1024);
	}
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	
	UWorld* World = GetWorld();
	if (!World) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;
	
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(false);
}
