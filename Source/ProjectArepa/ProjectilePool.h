// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectilePool.generated.h"

UCLASS()
class PROJECTAREPA_API AProjectilePool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectilePool();
	~AProjectilePool();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = ProjectilePool)
	class AProjectArepaProjectile * GetProjectile();

	UFUNCTION(BlueprintCallable, Category = ProjectilePool)
	void ReturnProjectile(class AProjectArepaProjectile * projectile);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectilePool)
	TArray<class AProjectArepaProjectile *> available_projectiles;
	
};
