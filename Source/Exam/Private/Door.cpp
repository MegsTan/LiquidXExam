// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

ADoor::ADoor()
{
	IsOpen = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

}

void ADoor::OnActionInteract_Implementation()
{
	Super::OnActionInteract_Implementation();

	if (!IsOpen)
	{
		FRotator NewRotation = FRotator(0.f, 90.f, 0.f);
		Mesh->AddRelativeRotation(FQuat(NewRotation), true, 0, ETeleportType::None);
		IsOpen = true;
	}
	else
	{
		FRotator NewRotation = FRotator(0.f, -90.f, 0.f);
		Mesh->AddRelativeRotation(FQuat(NewRotation), true, 0, ETeleportType::None);
		IsOpen = false;
	}
}