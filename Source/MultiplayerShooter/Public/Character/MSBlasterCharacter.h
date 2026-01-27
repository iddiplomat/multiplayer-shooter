#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MSBlasterCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
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
	
	void Jump(const FInputActionValue& Value);
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputMapping;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveForwardAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveRightAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> TurnAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookUpAction;
	
	UPROPERTY(VisibleAnywhere, Category=Camera)
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* FollowCamera;
};
