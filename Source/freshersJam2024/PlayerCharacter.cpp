// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create a camera arm to have the camera hang behind the player
    cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
    cameraArm->SetupAttachment(RootComponent);
    cameraArm->bUsePawnControlRotation = true;
    cameraArm->SetRelativeLocation(FVector(0, 64, 128));
    cameraArm->TargetArmLength = 200;
    // Create a camera and attach to the camera arm
    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera->SetupAttachment(cameraArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
    // Map inputs
    if (APlayerController* playerController = Cast<APlayerController>(Controller)) {
        if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer())) {
            subsystem->AddMappingContext(inputMappingContext, 0);
        }
    }
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind input actions to associated functions
    if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
        enhancedInputComponent->BindAction(walkInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Walk);
        enhancedInputComponent->BindAction(mouseInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MouseMovement);
    }
}

void APlayerCharacter::Walk(const FInputActionValue& value) {
    // Add movement input in correct direction(s)
    FVector2D direction = value.Get<FVector2D>();
    AddMovementInput(GetActorForwardVector(), direction.X);
    AddMovementInput(GetActorRightVector(), direction.Y);
}

void APlayerCharacter::MouseMovement(const FInputActionValue& value) {
    // Add correct rotation input(s)
    FVector2D mouseMovement = value.Get<FVector2D>();
    AddControllerYawInput(mouseMovement.X);
    AddControllerPitchInput(-mouseMovement.Y);
}

