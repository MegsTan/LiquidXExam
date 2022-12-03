// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class EXAM_API ADoor : public AInteractables
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADoor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void OnActionInteract_Implementation() override;

private:
	bool IsOpen = false;

};