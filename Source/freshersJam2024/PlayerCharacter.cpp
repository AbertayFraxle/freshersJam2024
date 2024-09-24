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
    HighlightLookAt();
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
        enhancedInputComponent->BindAction(interactInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
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

void APlayerCharacter::Interact(const FInputActionValue& value) {
    // Do stuff here
    if (lookedAt != nullptr) {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Interacting with highlighted object"));
    }
}

void APlayerCharacter::HighlightLookAt() {
    // Get forward vector for first raycast
    FVector ForwardVector = camera->GetForwardVector();
    // Get start point for first raycast
    FVector StartPoint = camera->GetComponentLocation();
    // Calculate endpoint for first raycast
    FVector EndPoint = StartPoint + (ForwardVector * interactionRange);
    // Create parameter list, just leaving blank for now
    FCollisionQueryParams Parameters;
    // Create raycast hit output
    FHitResult hit;
    // Var to hold whether we hit a valid target
    bool successfulHit = false;
    // Do our raycast
    if (GetWorld()->LineTraceSingleByChannel(hit, StartPoint, EndPoint, ECC_Visibility, Parameters)) {
        // Check that the hit actor has interactable tag, indicating it's an actor meant to be interacted with
        if (hit.GetActor()->ActorHasTag(TEXT("Interactable"))) {
            // Mark that we have successfully found a target, so second raycast isn't necessary
            successfulHit = true;
            // Remove highlight from previously targeted component, if we have one
            if (lookedAt != nullptr) {
                if (hit.GetActor()->GetUniqueID() != lookedAt->GetUniqueID()) {
                    lookedAt->SetRenderCustomDepth(false);
                }
            }
            // Store pointer to our new target
            lookedAt = hit.GetComponent();
            // Enable the highlight on our target
            lookedAt->SetRenderCustomDepth(true);
        }
        // If we don't find a target, make sure to remove highlight from our old one, if we did have one
        else {
            if (lookedAt != nullptr) {
                lookedAt->SetRenderCustomDepth(false);
                lookedAt = nullptr;
            }
        }
    }
}