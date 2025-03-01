// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::AddStateCpp(FVector2D key,bool newVal) {

	//inventoryStateNew.Add(key, newVal);
	inventoryStateNew.Add(key, newVal);
	
}

bool UInventory::FindStateCpp(FVector2D key, bool& value)
{

	bool* look = inventoryStateNew.Find(key);
	if (look) {
		value = *look;
		
		return true;
	}

	return false;

	
}
