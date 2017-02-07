// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectArepa.h"
#include "ProjectileMovementLibrary.h"
#include "Projectile.h"

FVector UProjectileMovementLibrary::LinearMovement(const class AProjectile * projectile)
{
	FVector new_loc = projectile->GetActorLocation();
	new_loc += projectile->velocity * FApp::GetDeltaTime();
	//new_loc.X += 200 * FApp::GetDeltaTime();
	return new_loc;
}

FVector UProjectileMovementLibrary::SinMovement(const class AProjectile * projectile)
{
	float amplitude = 250; //how strong the wave is
	float frequency = 15; //times it will do the sin wave
	float speed = projectile->speed * FApp::GetDeltaTime(); //bullet translaation

	FVector new_loc = projectile->GetActorLocation();
	float delta_height = FMath::Sin((projectile->running_time + FApp::GetDeltaTime()) * frequency) - FMath::Sin(projectile->running_time * frequency);

	FVector dir = projectile->velocity / projectile->speed;
	FVector orthogonal = FVector(-dir.Y, dir.X, 0);
	new_loc += dir * speed + orthogonal * amplitude * delta_height;

	return new_loc;
}



