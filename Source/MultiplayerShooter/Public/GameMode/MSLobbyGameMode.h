#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MSLobbyGameMode.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API AMSLobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
