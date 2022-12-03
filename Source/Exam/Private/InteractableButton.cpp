// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableButton.h"

AInteractableButton::AInteractableButton()
{
	IsTurnedOn = false;
}

// Called when the game starts or when spawned
void AInteractableButton::BeginPlay()
{
	Super::BeginPlay();

}

void AInteractableButton::OnActionInteract_Implementation()
{
	Super::OnActionInteract_Implementation();

	if (!IsTurnedOn)
	{
		FRotator NewRotation = FRotator(0.f, 0.f, -40.f);
		Mesh->AddRelativeRotation(FQuat(NewRotation), true, 0, ETeleportType::None);
		IsTurnedOn = true;
	}
	else
	{
		FRotator NewRotation = FRotator(0.f, 0.f, 40.f);
		Mesh->AddRelativeRotation(FQuat(NewRotation), true, 0, ETeleportType::None);
		IsTurnedOn = false;
	}
}