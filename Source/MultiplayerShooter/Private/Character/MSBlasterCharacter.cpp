#include "Character/MSBlasterCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMSBlasterCharacter::AMSBlasterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);
}

void AMSBlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(InputMapping, 0);
			}
		}
	}
}

void AMSBlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!Input) return;
	
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMSBlasterCharacter::Jump);
	Input->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AMSBlasterCharacter::MoveForward);
	Input->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMSBlasterCharacter::MoveRight);
	Input->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AMSBlasterCharacter::Turn);
	Input->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AMSBlasterCharacter::LookUp);
}

void AMSBlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMSBlasterCharacter::Jump(const FInputActionValue& Value)
{
	ACharacter::Jump();
}

void AMSBlasterCharacter::MoveForward(const FInputActionValue& Value)
{
	if (Controller != nullptr && Value.Get<float>() != 0.0f)
	{
		const FRotator YawRotation = FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value.Get<float>());
	}
}

void AMSBlasterCharacter::MoveRight(const FInputActionValue& Value)
{
	if (Controller != nullptr && Value.Get<float>() != 0.0f)
	{
		const FRotator YawRotation = FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value.Get<float>());
	}
}

void AMSBlasterCharacter::Turn(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}

void AMSBlasterCharacter::LookUp(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<float>());
}

