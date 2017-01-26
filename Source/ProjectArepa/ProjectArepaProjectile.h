// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "ProjectArepaProjectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class AUpgrade;

UCLASS(config=Game)
class AProjectArepaProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AProjectArepaProjectile();

	/** Function to handle the projectile hitting something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns ProjectileMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

public:

	void ApplyableUpgrades(TArray<AUpgrade*> current, TArray<AUpgrade*> impact);

	void FireInDirection(const FVector& shoot_direction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Upgrade)
	TArray<AUpgrade*> current_upgrades; //Important for the lifespan of the projectile

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Upgrade)
	TArray<AUpgrade*> impact_upgrades; //Important for when a projectile collide with some object
};

