// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteraction.h"
#include "Interactables.generated.h"

UCLASS()
class EXAM_API AInteractables : public AActor, public IIInteraction
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractables();

	UPROPERTY(EditAnywhere, Category = "Exam")
	class USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, Category = "Exam")
	class UBoxComponent* TriggerComponent;
	UPROPERTY(EditAnywhere, Category = "Exam")
	class UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// This is our function signature that we inherited from the interface and allows us to interact with this class.
	virtual void OnActionInteract_Implementation() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Is an interface function for interaction, this is exposed on blueprint which overrides the C++ function.
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Exam")
	void OnActionInteract();
};
