// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectArepa.h"
#include "Projectile.h"
#include "ProjectileMovementLibrary.h"


// Sets default values
AProjectile::AProjectile()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	static ConstructorHelpers::FObjectFinder<UMaterial> ProjectileMaterial(TEXT("/Game/Geometry/Materials/Bullet.Bullet"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scene_component = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = scene_component;

	projectile_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	projectile_mesh->SetStaticMesh(ProjectileMeshAsset.Object);
	projectile_mesh->SetMaterial(0, ProjectileMaterial.Object);
	//projectile_mesh->Set
	projectile_mesh->SetupAttachment(RootComponent);
	//projectile_mesh->BodyInstance.SetCollisionProfileName("Projectile");
	//projectile_mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something

	collision_component = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	collision_component->InitSphereRadius(15.0f);
	collision_component->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	collision_component->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	collision_component->SetupAttachment(RootComponent);
	collision_component->SetRelativeLocation(FVector::ZeroVector);
	//MovementFunction = &UProjectileMovementLibrary::LinearMovement;
	//Mfunction = &UProjectileMovementLibrary::LinearMovement;

	//MovementFunction = &UProjectileMovementLibrary::LinearMovement;
	MovementFunction = &UProjectileMovementLibrary::SinMovement;
	initial_speed = 3000.0f;
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	running_time += DeltaTime;
	FVector new_pos = MovementFunction(this);
	this->SetActorLocation(new_pos);
}

void AProjectile::FireInDirection(const FVector& shoot_direction)
{
	velocity = shoot_direction * initial_speed;
}

void AProjectile::Setup()
{
	//Set timer with lifespan and methods
}

void AProjectile::AdvanceTimer()
{

}

void AProjectile::TimerOver()
{
	//Use this to deactivate projectile aand send back to pool
	OnLifeOver.Broadcast(this);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Make it bounce
	FVector p = this->GetActorForwardVector();
	float dot = FVector::DotProduct(p, Hit.Normal);
	dot *= -2;
	FVector normal_dot = Hit.Normal * dot;
	p = p + normal_dot;

	this->SetActorRelativeLocation(p);

}

////FVector(*new_function)(const AProjectile * projectile)
void AProjectile::SetMovementFunction(TEnumAsByte<EMovementType> selected_movement)
{
	//This switch needs to be modified same as the enum for adding new types of movements 
	switch (selected_movement)
	{
	case EMovementType::MT_Linear:
		MovementFunction = &UProjectileMovementLibrary::LinearMovement;
		break;
	case EMovementType::MT_Sin:
		MovementFunction = &UProjectileMovementLibrary::SinMovement;
		break;
	default:
		break;
	}

}