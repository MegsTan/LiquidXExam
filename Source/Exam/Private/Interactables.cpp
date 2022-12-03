// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables.h"
#include "Components/BoxComponent.h"
#include "UObject/Object.h"
#include "Components/SceneComponent.h"

// Sets default values
AInteractables::AInteractables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	RootComponent = SceneComponent;

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponent"));
	TriggerComponent->InitBoxExtent(FVector(100.f, 100.f, 100.f));
	TriggerComponent->SetCollisionProfileName(TEXT("Trigger"));
	TriggerComponent->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractables::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractables::OnActionInteract_Implementation()
{

}