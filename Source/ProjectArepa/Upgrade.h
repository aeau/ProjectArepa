// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Upgrade.generated.h"

class AProjectile;

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	UT_OneUse		UMETA(DisplayName = "OneUse"),
	UT_Preprocess 	UMETA(DisplayName = "Preprocess"),
	UT_Current 		UMETA(DisplayName = "Current"),
	UT_Impact		UMETA(DisplayName = "Impact")
};

UCLASS(Blueprintable)
class PROJECTAREPA_API AUpgrade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpgrade();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* overlap_comp,
						class AActor* other_actor,
						class UPrimitiveComponent* other_comp,
						int32 other_index,
						bool from_sweep,
						const FHitResult & sweep_result);

	UFUNCTION(BlueprintNativeEvent)
	void Process(AProjectile * projectile, class AProjectArepaPawn * player);

public:

	UPROPERTY(Category = Mesh, EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* upgrade_mesh;

	UPROPERTY(Category = scene, EditDefaultsOnly, BlueprintReadWrite)
	class USceneComponent * scene_component;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Upgrade)
	UBoxComponent* trigger_component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Upgrade)
	EUpgradeType UpgradeType;
	
};
