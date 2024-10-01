// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InteractableComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FRESHERSJAM2024_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement functions
	void Walk(const FInputActionValue& value);
	void MouseMovement(const FInputActionValue& value);

	// Interact function
	void Interact(const FInputActionValue& value);

	// Highlight Interactable
	void HighlightLookAt();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* walkInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* mouseInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* interactInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* inventoryInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* inputMappingContext;

	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* cameraArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* camera;

	// Interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float interactionRange = 1500;
	UPrimitiveComponent* lookedAt;

};
