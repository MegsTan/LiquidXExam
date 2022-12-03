// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GlobalLog.h"


//////////////////////////////////////////////////////////////////////////
// AExamCharacter

AExamCharacter::AExamCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Component"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AExamCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AExamCharacter::OnOverlapEnd);

	Interactables = NULL;
	JumpCount = 0;
	JumpForce = 700.f;
	CurrentJumpForce = 700.f;
}

void AExamCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AExamCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExamCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExamCharacter::Look);

		EnhancedInputComponent->BindAction(OnInteractAction, ETriggerEvent::Triggered, this, &AExamCharacter::OnInteract);

		PlayerInputComponent->BindAction("OnInteractionKeyPressed", IE_Pressed, this, &AExamCharacter::OnInteract);

		PlayerInputComponent->BindAction("OnJumpKeyPressed", IE_Pressed, this, &AExamCharacter::OnJumpPressed);
		PlayerInputComponent->BindAction("OnJumpKeyPressed", IE_Released, this, &AExamCharacter::OnJumpReleased);
	}

}

void AExamCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AExamCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AExamCharacter::OnJumpPressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("ON JUMP"));
	bPressedJump = true;

	if (JumpCount <= 1)
	{
		if (JumpCount == 1)
		{
			CurrentJumpForce *= 2;
		}

		GetCharacterMovement()->Velocity += FVector(0, 0, 1) * CurrentJumpForce;
		JumpCount++;
	}
}

void AExamCharacter::OnJumpReleased()
{
	bPressedJump = false;
}

void AExamCharacter::Landed(const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("LANDED"));
	JumpCount = 0;
	CurrentJumpForce = JumpForce;
}

void AExamCharacter::OnInteract()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("ON INTERACT"));
	if (Interactables != NULL)
	{
		if (Interactables->GetClass()->ImplementsInterface(UIInteraction::StaticClass()))
		{
			IIInteraction::Execute_OnActionInteract(Interactables);
		}
	}
}

void AExamCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherActor->GetClass()->IsChildOf(AInteractables::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Turquoise, FString::Printf(TEXT("This: %s"), *Interactables->GetName()));
		Interactables = Cast<AInteractables>(OtherActor);
	}
}

void AExamCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Interactables = NULL;
	}
}