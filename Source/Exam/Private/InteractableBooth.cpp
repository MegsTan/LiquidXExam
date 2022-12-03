// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBooth.h"
#include "Components/WidgetComponent.h"

AInteractableBooth::AInteractableBooth()
{
	BoothWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	BoothWidget->SetupAttachment(BoothWidget);
}

// Called when the game starts or when spawned
void AInteractableBooth::BeginPlay()
{
	Super::BeginPlay();

}

void AInteractableBooth::OnActionInteract_Implementation()
{
	Super::OnActionInteract_Implementation();

}