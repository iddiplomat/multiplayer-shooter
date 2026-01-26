#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MSBlasterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MULTIPLAYERSHOOTER_API AMSBlasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMSBlasterCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	USpringArmComponent* CameraBoom;
	UCameraComponent* FollowCamera;
};
