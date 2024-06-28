
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PrimitiveFountain.generated.h"

UCLASS()
class FIRSTGAME_API APrimitiveFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrimitiveFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain")
	UStaticMesh* PrimitiveMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain")
	float SpawnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain")
	float PrimitiveSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain")
	UMaterialInterface* PrimitiveMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain")
	FVector LaunchVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain")
	int32 NumPrimitivesPerSpawn;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain")
	float LaunchVelocityVariation;  // �������䷽��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain")
	float PrimitiveLifetime;  // ���Ƽ��������������

private:
	float TimeSinceLastSpawn;
	void SpawnPrimitive();
	void DestroyPrimitive(AActor* Primitive);
};
