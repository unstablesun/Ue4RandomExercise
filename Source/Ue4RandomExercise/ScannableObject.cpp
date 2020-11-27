
#include "ScannableObject.h"


AScannableObject::AScannableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	scanID = -1;

	SetMeshMatArrays();

	for (int i = 0; i < 10; i++)
	{
		const FString mName = meshNames[i];
		const TCHAR* meshFilename = *mName;
		ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(meshFilename);

		UStaticMesh* Asset = MeshAsset.Object;
		staticMeshInstArray.Add(Asset);

		TArray<FString> Out;
		mName.ParseIntoArray(Out, TEXT("."), true);
		scanNames.Add(Out[1]);
	}
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetStaticMesh(staticMeshInstArray[0]);
	StaticMeshComp->SetSimulatePhysics(true);

	const FString matName = materialNames[0];
	const TCHAR* matFilename = *matName;
	ConstructorHelpers::FObjectFinder<UMaterialInterface> FoundMaterial(matFilename);
	MeshMaterial = FoundMaterial.Object;
	StaticMeshComp->SetMaterial(0, MeshMaterial);

}




void AScannableObject::SetScanID(int32 id)
{
	scanID = id;
}

FString AScannableObject::GetScanObjString()
{
	return scanObjString;

}

void AScannableObject::BeginPlay()
{
	Super::BeginPlay();

	int32 size = staticMeshInstArray.Num();
	int32 s = FMath::RandRange(0, size - 1);
	StaticMeshComp->SetStaticMesh(staticMeshInstArray[s]);

	UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(MeshMaterial, StaticMeshComp);

	float r = FMath::FRandRange(0, 1);
	float g = FMath::FRandRange(0, 1);
	float b = FMath::FRandRange(0, 1);
	dynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(r, g, b));

	float metallic = FMath::FRandRange(0, 1);
	dynamicMaterial->SetScalarParameterValue(TEXT("Metallic"), metallic);

	float roughness = FMath::FRandRange(0, 1);
	dynamicMaterial->SetScalarParameterValue(TEXT("Roughness"), roughness);

	float specular = FMath::FRandRange(0, 1);
	dynamicMaterial->SetScalarParameterValue(TEXT("Specular"), specular);

	StaticMeshComp->SetMaterial(0, dynamicMaterial);


	const TCHAR* temp = *scanNames[s];;
	scanObjString = FString::Printf(TEXT("scan%s%d"), temp, scanID);

}

void AScannableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AScannableObject::SetMeshMatArrays()
{
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/corerods.corerods'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/deflatedball.deflatedball'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/gasket.gasket'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/paperfold.paperfold'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/pincushion.pincushion'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/protonbarrel.protonbarrel'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/quartz.quartz'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/radar.radar'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/rubicsmess.rubicsmess'"));
	meshNames.Add(TEXT("StaticMesh'/Game/GameSim/Assets/shizzle.shizzle'"));


	materialNames.Add(TEXT("Material'/Game/GameSim/Assets/M_Primary.M_Primary'"));


}