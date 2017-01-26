// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectArepa.h"
#include "Upgrade.h"
#include "ProjectArepaPawn.h"
#include "ProjectArepaProjectile.h"


// Sets default values
AUpgrade::AUpgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FAttachmentTransformRules attachment_rules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);

	scene_component = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = scene_component;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	upgrade_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpgradeMesh"));
	//upgrade_mesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	//upgrade_mesh->SetStaticMesh(ShipMesh.Object);
	upgrade_mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	

	trigger_component = CreateDefaultSubobject<UBoxComponent>(TEXT("trigger"));
	trigger_component->OnComponentBeginOverlap.AddDynamic(this, &AUpgrade::OnBeginOverlap);
	trigger_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//RootComponent = trigger_component;
}

// Called when the game starts or when spawned
void AUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUpgrade::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AUpgrade::OnBeginOverlap(class UPrimitiveComponent* overlap_comp,
							  class AActor* other_actor,
							  class UPrimitiveComponent* other_comp,
							  int32 other_index,
							  bool from_sweep,
							  const FHitResult & sweep_result)
{
	if (other_actor != this)
	{
		AProjectArepaPawn* player = Cast<AProjectArepaPawn>(other_actor);
		if (player)
		{
			player->FillUpgrades(this);
		}
	}
}

void AUpgrade::Process_Implementation(AProjectArepaProjectile * projectile, class AProjectArepaPawn * player)
{

}
