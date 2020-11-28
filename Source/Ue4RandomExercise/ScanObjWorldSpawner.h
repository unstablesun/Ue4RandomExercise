// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScannableObject.h"
#include "ScanObjWorldSpawner.generated.h"

UCLASS()
class UE4RANDOMEXERCISE_API AScanObjWorldSpawner : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "AScanObjWorldSpawner")
		TSubclassOf<AActor> ActorToSpawn;


public:
	// Sets default values for this actor's properties
	AScanObjWorldSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spanX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spanY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float incX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float incY;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void SpawnObjectA(FVector vec, FRotator rot);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float elaspedTime;
	float maxTime;

	float StartX;
	float StartY;
	float StoredX;
	float StoredY;

	FVector location;
	FRotator rotation;

	bool firstpass;

	int32 ObjectCount;

	void TurnOffPhysics();

	TArray<AScannableObject*> scannableObjects;


	enum SpawnState
	{
		init,
		spawn,
		wait,
		physicsOff,
		idle
	};
	SpawnState spawnState;

};
