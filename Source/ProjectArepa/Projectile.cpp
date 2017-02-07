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
	projectile_mesh->SetupAttachment(RootComponent);
	projectile_mesh->CastShadow = 0;
	projectile_mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	//RootComponent = projectile_mesh;
	//projectile_mesh->BodyInstance.SetCollisionProfileName("Projectile");
	//projectile_mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something
	//projectile_mesh->SetNotifyRigidBodyCollision(true);

	collision_component = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	collision_component->InitSphereRadius(50.0f);
	collision_component->BodyInstance.SetCollisionProfileName("Projectile");
	collision_component->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	collision_component->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	collision_component->bHiddenInGame = false;
	collision_component->SetupAttachment(RootComponent);
	//RootComponent = collision_component;
	//collision_component->SetRelativeLocation(FVector::ZeroVector);
	//collision_component->SetNotifyRigidBodyCollision(true);

	/*collision_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);*/
	collision_component->SetCollisionResponseToAllChannels(ECR_Ignore);

	//projectile_mesh->SetRelativeLocation(FVector::ZeroVector);
	//this->SetActorEnableCollision(true);
	//this->OnActorHit.AddDynamic(this, &AProjectile::Hit);

	//this->SetActorEnableCollision(true);
	//collision_component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//projectile_mesh->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	//MovementFunction = &UProjectileMovementLibrary::LinearMovement;
	//Mfunction = &UProjectileMovementLibrary::LinearMovement;

	MovementFunction = &UProjectileMovementLibrary::LinearMovement;
	//MovementFunction = &UProjectileMovementLibrary::SinMovement;

	speed = 2000.0f;
	life_span = 3.0f;
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
	UE_LOG(LogTemp, Warning, TEXT("SETUP DIRECTION"));
	direction = shoot_direction;
	velocity = shoot_direction * speed;
}

void AProjectile::Setup()
{
	//Set timer with lifespan and methods
	GetWorldTimerManager().SetTimer(return_to_pool_timer, this, &AProjectile::TimerOver, life_span, false);
}

void AProjectile::AdvanceTimer()
{

}

void AProjectile::TimerOver()
{
	//Use this to deactivate projectile aand send back to pool
	OnLifeOver.Broadcast(this);
}

void AProjectile::OnBeginOverlap(	class UPrimitiveComponent* overlap_comp,
									class AActor* other_actor,
									class UPrimitiveComponent* other_comp,
									int32 other_index,
									bool from_sweep,
									const FHitResult & sweep_result)
{
	UE_LOG(LogTemp, Warning, TEXT("COMPONENT IS OVERLAPING!!"));

	//Because overlap don't do anything with the hit (is empty always)
	//is needeed to perform a raycast to get the hit and the normal for the bounciness
	//raycast
	FHitResult hit = FHitResult(ForceInit);
	FVector end = FVector::ZeroVector;
	end = this->GetActorLocation() + (direction * 5000);
	FCollisionQueryParams TraceParams;
	TraceParams.TraceTag = "WeaponTrace";
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	//raycast
	GetWorld()->LineTraceSingleByChannel(hit, this->GetActorLocation(), end, ECollisionChannel::ECC_WorldStatic, TraceParams);

	if (hit.Actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit normal %s"), *hit.Normal.ToString());
		//Bounce
		direction.X = hit.Normal.X != 0 ? direction.X * -1.0f : direction.X;
		direction.Y = hit.Normal.Y != 0 ? direction.Y * -1.0f : direction.Y;
		direction.Z = hit.Normal.Z != 0 ? direction.Z * -1.0f : direction.Z;

		velocity = direction * speed;
	}
	
	//if you want to debug
	//DrawDebugLine(GetWorld(), this->GetActorLocation(), end, FColor::Cyan, false, 10.0f, 10, 12.333f);

}


void AProjectile::Hit(AActor* self, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("ACTOR IS COLLIDING!!!"));
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I'M COLLIDING!!!"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("I'M COLLIDING!!!"));

	//Make it bounce
	/*FVector p = this->GetActorForwardVector();
	float dot = FVector::DotProduct(p, Hit.Normal);
	dot *= -2;
	FVector normal_dot = Hit.Normal * dot;
	p = p + normal_dot;

	this->SetActorRelativeLocation(p);*/
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