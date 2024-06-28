

#include "PrimitiveFountain.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"


// Sets default values
APrimitiveFountain::APrimitiveFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnRate = 1.0f;
	PrimitiveSize = 1.0f;
	LaunchVelocity = FVector(0.0f, 0.0f, 500.0f);
	TimeSinceLastSpawn = 0.0f;
	NumPrimitivesPerSpawn = 5;  // 默认值
	LaunchVelocityVariation = 100.0f;  // 默认值，控制喷射方向的随机性
	PrimitiveLifetime = 5.0f;
}

// Called when the game starts or when spawned
void APrimitiveFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrimitiveFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastSpawn += DeltaTime;
	if (TimeSinceLastSpawn >= 1.0f / SpawnRate)
	{
		SpawnPrimitive();
		TimeSinceLastSpawn = 0.0f;
	}
}

void APrimitiveFountain::SpawnPrimitive()
{
	if (PrimitiveMesh)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			for (int32 i = 0; i < NumPrimitivesPerSpawn; ++i)
			{
				FActorSpawnParameters SpawnParams;
				FVector SpawnLocation = GetActorLocation();
				FRotator SpawnRotation = GetActorRotation();

				AActor* NewPrimitiveActor = World->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				if (NewPrimitiveActor)
				{
					UStaticMeshComponent* NewPrimitiveComponent = NewObject<UStaticMeshComponent>(NewPrimitiveActor);
					if (NewPrimitiveComponent)
					{
						NewPrimitiveComponent->SetStaticMesh(PrimitiveMesh);
						NewPrimitiveComponent->SetWorldScale3D(FVector(PrimitiveSize));
						NewPrimitiveComponent->SetMaterial(0, PrimitiveMaterial);
						NewPrimitiveComponent->RegisterComponent();
						NewPrimitiveComponent->AttachToComponent(NewPrimitiveActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
						NewPrimitiveComponent->SetSimulatePhysics(true);

						FVector RandomLaunchVelocity = LaunchVelocity + FVector(FMath::RandRange(-LaunchVelocityVariation, LaunchVelocityVariation), FMath::RandRange(-LaunchVelocityVariation, LaunchVelocityVariation), FMath::RandRange(0.0f, LaunchVelocityVariation));
						NewPrimitiveComponent->AddImpulse(RandomLaunchVelocity * NewPrimitiveComponent->GetMass());

						// 设置定时器以销毁几何体
						FTimerHandle TimerHandle;
						World->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &APrimitiveFountain::DestroyPrimitive, NewPrimitiveActor), PrimitiveLifetime, false);

					}
				}
			}
			
		}
	}

}

void APrimitiveFountain::DestroyPrimitive(AActor* Primitive)
{
	if (Primitive)
	{
		Primitive->Destroy();
	}
}

