// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RobotDrone.generated.h"

UCLASS()
class UE4RANDOMEXERCISE_API ARobotDrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARobotDrone();


	UFUNCTION(BlueprintCallable)
		bool TakeScreenShot();

	UFUNCTION(BlueprintCallable)
		bool GetAllActorsInCameraView(float tolerance);

	UFUNCTION(BlueprintCallable)
		bool StartNextSequence();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	int32 fnameIndex;

	bool WriteActorsToFile(TArray<AActor*> onScreenActors);


};
