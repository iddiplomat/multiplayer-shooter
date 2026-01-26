#include "Character/MSBlasterCharacter.h"

AMSBlasterCharacter::AMSBlasterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMSBlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMSBlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMSBlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

