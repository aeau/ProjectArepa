// Copyright 1998-2016 Epic Games, Inc. All Rights Reserve

#include "ProjectArepa.h"
#include "ProjectArepaProjectile.h"
#include "Upgrade.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectArepaProjectile::AProjectArepaProjectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectArepaProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->Bounciness = 0.3f;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	ProjectileMovement->Activate(false);

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AProjectArepaProjectile::ApplyableUpgrades(TArray<AUpgrade*> current, TArray<AUpgrade*> impact)
{
	current_upgrades = current;
	impact_upgrades = impact;
}

void AProjectArepaProjectile::FireInDirection(const FVector& shoot_direction)
{
	for (auto& upgrade : current_upgrades)
	{
		//upgrade->Process(this, NULL);
	}

	ProjectileMovement->SetComponentTickEnabled(true);
	ProjectileMovement->Activate(true);
	ProjectileMovement->Velocity = shoot_direction * ProjectileMovement->InitialSpeed;
}

void AProjectArepaProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	for (auto& upgrade : impact_upgrades)
	{
		//upgrade->Process(this, NULL);
	}

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	//Destroy();
}