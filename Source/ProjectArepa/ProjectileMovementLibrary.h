// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjectileMovementLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAREPA_API UProjectileMovementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "ProjectileMovement")
	static FVector LinearMovement(const class AProjectile * projectile);

	UFUNCTION(BlueprintCallable, Category = "ProjectileMovement")
	static FVector SinMovement(const class AProjectile * projectile);
	
	
};
