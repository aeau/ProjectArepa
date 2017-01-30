// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectArepa.h"
#include "ProjectileMovementLibrary.h"
#include "Projectile.h"

FVector UProjectileMovementLibrary::LinearMovement(const class AProjectile * projectile)
{
	FVector new_loc = projectile->GetActorLocation();
	new_loc.X += 200 * FApp::GetDeltaTime();
	return new_loc;
}

FVector UProjectileMovementLibrary::SinMovement(const class AProjectile * projectile)
{
	FVector new_loc = projectile->GetActorLocation();
	float delta_height = FMath::Sin(projectile->running_time + FApp::GetDeltaTime()) - FMath::Sin(projectile->running_time);
	new_loc.Y += delta_height * 200; 
	new_loc.X += 200 * FApp::GetDeltaTime();
	return new_loc;
}



