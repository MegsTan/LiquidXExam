// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInteraction : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class EXAM_API IIInteraction
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Exam")
	void OnActionInteract();
};
