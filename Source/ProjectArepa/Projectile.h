// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementLibrary;

//TODO: Maybe change this to don't be multicast
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReturnToPool, class AProjectile*, projectile);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	MT_Linear		UMETA(DisplayName = "LinearMovement"),
	MT_Sin 			UMETA(DisplayName = "SinMovement")
};

UCLASS()
class PROJECTAREPA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* projectile_mesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	USphereComponent * collision_component;

	UPROPERTY(BlueprintAssignable)
	FReturnToPool OnLifeOver;

	FVector(*MovementFunction)(const AProjectile * projectile);

	FTimerHandle return_to_pool_timer;
	
	float running_time;
	float initial_speed;
	float life_span;
	FVector velocity;

public:

	//Missing setup function which will set up a timer for lifespan
	//and maybe delegate to return to pool

	//typedef FVector(*Funcs)(const AProjectile * projectile);

	UFUNCTION(BlueprintCallable, Category = MovementFunction)
	void SetMovementFunction(TEnumAsByte<EMovementType> selected_movement);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void FireInDirection(const FVector& shoot_direction);

	void Setup();
	void AdvanceTimer();
	void TimerOver();

	//typename FInputAxisHandlerSignature::TUObjectMethodDelegate< UserClass >::FMethodPtr Func
	//TFunctionRef < FVector(FVector pos)> Mfunction;

};
