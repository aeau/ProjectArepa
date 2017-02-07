// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectArepa.h"
#include "ProjectilePool.h"
#include "Projectile.h"


// Sets default values
AProjectilePool::AProjectilePool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	

}

AProjectilePool::~AProjectilePool()
{
	available_projectiles.Empty();
}

// Called when the game starts or when spawned
void AProjectilePool::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();

	for (int i = 0; i < 50; ++i)
	{
		//TSharedPtr<AProjectArepaProjectile> projectile = MakeShareable(World->SpawnActor<AProjectArepaProjectile>(FVector::ZeroVector, FRotator::ZeroRotator));
		if (World)
		{
			AProjectile * projectile = World->SpawnActor<AProjectile>(FVector::ZeroVector, FRotator::ZeroRotator);
			projectile->SetActorHiddenInGame(true);
			projectile->GetProjectileCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			projectile->OnLifeOver.AddDynamic(this, &AProjectilePool::ReturnProjectile);
			available_projectiles.Add(projectile);
		}
	}
}

class AProjectile * AProjectilePool::GetProjectile()
{
	if (available_projectiles.Num() == 0)
	{
		return nullptr;
	}

	AProjectile * projectile = available_projectiles.Pop();
	projectile->SetActorHiddenInGame(false);
	projectile->GetProjectileCollider()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	projectile->GetProjectileCollider()->SetCollisionResponseToAllChannels(ECR_Overlap);
	projectile->Setup();
	return projectile;

	//UWorld* const World = GetWorld();

	////TSharedPtr<AProjectArepaProjectile> projectile = MakeShareable(World->SpawnActor<AProjectArepaProjectile>(FVector::ZeroVector, FRotator::ZeroRotator));
	//if (World)
	//{
	//	AProjectArepaProjectile * projectile = World->SpawnActor<AProjectArepaProjectile>(FVector::ZeroVector, FRotator::ZeroRotator);
	//	return projectile;
	//}

	//return nullptr;
}

void AProjectilePool::ReturnProjectile(class AProjectile * projectile)
{
	projectile->SetActorHiddenInGame(true);
	projectile->GetProjectileCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	projectile->GetProjectileCollider()->SetCollisionResponseToAllChannels(ECR_Ignore);
	available_projectiles.Push(projectile);
}


