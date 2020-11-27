// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotDrone.h"

// Sets default values
ARobotDrone::ARobotDrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARobotDrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobotDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARobotDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

