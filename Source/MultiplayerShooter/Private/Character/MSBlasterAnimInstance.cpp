#include "Character/MSBlasterAnimInstance.h"

#include "Character/MSBlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMSBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	BlasterCharacter = Cast<AMSBlasterCharacter>(TryGetPawnOwner());
}

void UMSBlasterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	
	if (!BlasterCharacter)
	{
		BlasterCharacter = Cast<AMSBlasterCharacter>(TryGetPawnOwner());
	}
	
	if (!BlasterCharacter) return;
	
	FVector Velocity = BlasterCharacter->GetVelocity();
	Velocity.Z = 0.0f;
	Speed = Velocity.Size();
	
	bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();
	
	bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f;
}
