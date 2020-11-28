// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotDrone.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "ScannableObject.h"


// Sets default values
ARobotDrone::ARobotDrone()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fnameIndex = 1;

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


bool ARobotDrone::StartNextSequence()
{
	fnameIndex++;

	return true;
}

bool ARobotDrone::TakeScreenShot()
{
#if WITH_EDITOR
	const FString SavedDataDirectory = FString::Printf(TEXT("%s/%s"), *FPaths::ProjectSavedDir(), TEXT("Data"));
#else
	const FString SavedDataDirectory = FString::Printf(TEXT("%s/../%s"), *FPaths::ProjectSavedDir(), TEXT("Data"));
#endif

	const FString ImageFilename = FString::Printf(TEXT("%s/Image_%d.png"), *SavedDataDirectory, fnameIndex);

	FScreenshotRequest::RequestScreenshot(ImageFilename, false, false);

	//UE_LOG(LogTemp, Warning, TEXT("FScreenshotRequest: Written: %s"), *ImageFilename);

	return true;
}






bool ARobotDrone::GetAllActorsInCameraView(float tolerance)
{
	
	TSubclassOf<AActor> classToFind;
	classToFind = AActor::StaticClass();
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundActors);

	TArray<AActor*> onScreenActors;
	


	for (AActor* Actor : foundActors)
	{
		//UPrimitiveComponent *primComp = (UPrimitiveComponent*)Actor->GetComponentByClass(TSubclassOf <UPrimitiveComponent>());
		UPrimitiveComponent* primComp = (UPrimitiveComponent*)Actor->GetComponentByClass(UPrimitiveComponent::StaticClass());

		if (primComp != nullptr)
		{
			UWorld* World = primComp->GetWorld();

			float lastTime = primComp->GetLastRenderTimeOnScreen();

			if ((World->GetTimeSeconds() - lastTime) <= tolerance)
			{
				onScreenActors.Add(Actor);
			}
		}
	}

	WriteActorsToFile(onScreenActors);

	return true;
}

bool ARobotDrone::WriteActorsToFile(TArray<AActor*> onScreenActors)
{
	//create path + fname
	FString file = FString::Printf(TEXT("%s/%s"), *FPaths::ProjectSavedDir(), TEXT("Data"));
	file.Append(FString::Printf(TEXT("/Image_%d_actors.txt"), fnameIndex));

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	FString StringToWrite(FString::Printf(TEXT("List of actors in camera view for sequence : %d\n\n"), fnameIndex));

	for (AActor* Actor : onScreenActors)
	{
		AScannableObject* ScanActor = Cast<AScannableObject>(Actor);
		FString ActorLable = Actor->GetActorLabel();
		//FString ActorScanStr = ScanActor->GetScanObjString(); //error not set yet
		StringToWrite.Append(ActorLable);
		StringToWrite.Append(TEXT(" : "));
		//StringToWrite.Append(ActorScanStr);
		StringToWrite.Append(FString::Printf(TEXT("\n")));
	}

	//file is always new, no checks needed
	if (FFileHelper::SaveStringToFile(StringToWrite, *file))
	{
		UE_LOG(LogTemp, Warning, TEXT("File written: \"%s\""), *StringToWrite);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to write file."));
	}

	return true;
}




