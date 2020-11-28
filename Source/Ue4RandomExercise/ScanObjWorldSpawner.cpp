// Fill out your copyright notice in the Description page of Project Settings.


#include "ScanObjWorldSpawner.h"

// Sets default values
AScanObjWorldSpawner::AScanObjWorldSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	elaspedTime = 0;
	maxTime = 0.005;
	firstpass = true;
	SpawnObjects = true;

	location = GetActorLocation();
	rotation = FRotator(0, 0, 0);


	ObjectCount = 0;
}

// Called when the game starts or when spawned
void AScanObjWorldSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void AScanObjWorldSpawner::SpawnObjectA(FVector loc, FRotator rot)
{
	FActorSpawnParameters SpawnParams;


	AScannableObject* SpawnActorRef = GetWorld()->SpawnActor<AScannableObject>(ActorToSpawn, loc, rot, SpawnParams);

	SpawnActorRef->SetScanID(++ObjectCount);

	scannableObjects.Add(SpawnActorRef);
}

// Called every frame
void AScanObjWorldSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnObjects)
	{
		elaspedTime += DeltaTime;
		if (elaspedTime >= maxTime)
		{
			if (firstpass == true)
			{
				firstpass = false;
				location = GetActorLocation();
				StartX = spanX;
				StartY = spanY;
				StoredX = -StartX;
				StoredY = -StartY;
				location.X = StoredX;
				location.Y = StoredY;
			}

			elaspedTime = 0;

			SpawnObjectA(location, rotation);

			float jitter = FMath::FRandRange(0, 500);

			StoredX += incX;
			location.X = StoredX + jitter;

			location.Y = StoredY;
			jitter = FMath::FRandRange(0, 500);
			int32 neg = FMath::RandRange(0, 100);
			if (neg < 50)
				location.Y += jitter;
			else
				location.Y -= jitter;

			if (StoredX > StartX)
			{
				StoredX = -StartX;
				location.X = -StartX;

				StoredY += incY;
				location.Y = StoredY;

				if (location.Y > StartY)
				{
					SpawnObjects = false;

				}

			}

			float yaw = FMath::FRandRange(0, 360);
			rotation.Yaw = yaw;

			float pitch = FMath::FRandRange(0, 360);
			rotation.Pitch = pitch;

			float roll = FMath::FRandRange(0, 360);
			rotation.Roll = roll;

		}
	}
	else
	{
		elaspedTime += DeltaTime;
		if (elaspedTime >= 2)
		{
			elaspedTime = 0;
		}
	}

}

void AScanObjWorldSpawner::TurnOffPhysics()
{
	for (AScannableObject* Actor : scannableObjects)
	{
		Actor->StaticMeshComp->SetSimulatePhysics(false);
	}
}


