// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScannableObject.generated.h"

UCLASS()
class UE4RANDOMEXERCISE_API AScannableObject : public AActor
{
	GENERATED_BODY()

public:
	AScannableObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* MeshMaterial;

	void SetScanID(int32 id);

	FString GetScanObjString();


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void SetMeshMatArrays();

	TArray<FString> meshNames;
	TArray<FString> scanNames;
	TArray<FString> materialNames;

	TArray<UStaticMesh*> staticMeshInstArray;

	int32 scanID;
	FString scanObjString;

};
