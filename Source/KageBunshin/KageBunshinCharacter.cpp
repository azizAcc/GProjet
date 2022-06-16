// Copyright Epic Games, Inc. All Rights Reserved.

#include "KageBunshinCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// AKageBunshinCharacter

AKageBunshinCharacter::AKageBunshinCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 660.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

    // 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
    // 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
    // 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
    // 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    // 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;
}

//////////////////////////////////////////////////////////////////////////
// Animation

void AKageBunshinCharacter::UpdateAnimation()
{
	//const FVector PlayerVelocity = GetVelocity();
	//const float PlayerSpeedSqr = PlayerVelocity.X;
	//const float PlayerSpeedMovement = PlayerVelocity.Z;
	//// Are we moving or standing still?

	//UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningRight : IdleRight;
	//UPaperFlipbook* LeftAnimation = (PlayerSpeedSqr < 0.0f) ? RunningLeft : IdleLeft;
	//UPaperFlipbook* UpAnimation = (PlayerSpeedMovement > 0.0f) ? RunningUp : IdleUp;
	//UPaperFlipbook* DownAnimation = (PlayerSpeedMovement < 0.0f) ? RunningDown : IdleDown;

	//if (GoingRight)
	//{
	//	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	//	{

	//		GetSprite()->SetFlipbook(DesiredAnimation);
	//	}
	//}
	//if (GoingLeft)
	//{
	//	if (GetSprite()->GetFlipbook() != LeftAnimation)
	//	{

	//		GetSprite()->SetFlipbook(LeftAnimation);
	//	}
	//}
	//if (GoingDown)
	//{
	//	if (GetSprite()->GetFlipbook() != DownAnimation)
	//	{

	//		GetSprite()->SetFlipbook(DownAnimation);
	//	}
	//}
	//if (GoingUp)
	//{
	//	if (GetSprite()->GetFlipbook() != UpAnimation)
	//	{

	//		GetSprite()->SetFlipbook(UpAnimation);
	//	}
	//}

}

void AKageBunshinCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateCharacter();	
}

void AKageBunshinCharacter::LeftOrRight(float Value)
{
	//if (Value > 0)
	//{
	//	GoingDown = false;
	//	GoingRight = true;
	//	GoingLeft = false;
	//	GoingUp = false;
	//}
	//if (Value < 0)
	//{
	//	GoingDown = false;
	//	GoingRight = false;
	//	GoingLeft = true;
	//	GoingUp = false;
	//}
	//AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AKageBunshinCharacter::UpOrDown(float Value)
{
	//if (Value > 0)
	//{
	//	GoingDown = false;
	//	GoingRight = false;
	//	GoingLeft = false;
	//	GoingUp = true;
	//}
	//if (Value < 0)
	//{
	//	GoingDown = true;
	//	GoingRight = false;
	//	GoingLeft = false;
	//	GoingUp = false;
	//}
	//AddMovementInput(FVector(0.0f, 0.0f, 1.0f), Value);
}


//////////////////////////////////////////////////////////////////////////
// Input

void AKageBunshinCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAxis("LeftOrRight", this, &AKageBunshinCharacter::LeftOrRight);
	PlayerInputComponent->BindAxis("UpOrDown", this, &AKageBunshinCharacter::UpOrDown);
	
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AKageBunshinCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AKageBunshinCharacter::TouchStopped);
}

void AKageBunshinCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Jump on any touch
	Jump();
}

void AKageBunshinCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Cease jumping once touch stopped
	StopJumping();
}

void AKageBunshinCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	//UpdateAnimation();
}
