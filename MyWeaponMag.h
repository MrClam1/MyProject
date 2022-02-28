// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyWeaponMag.generated.h"

class USphereComponent;

UCLASS()
class MYPROJECT_API AMyWeaponMag : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyWeaponMag();

	void SetFireDirection(const FVector& Direction) { FireDirection = Direction; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MyComponents")
	USphereComponent* CollusionComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MyComponents")
	UProjectileMovementComponent* MovementComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "WeaponInfo")
	float Radius = 200.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "WeaponInfo")
	float Damage = 50.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "WeaponInfo")
	bool bDoFullDamage = false;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "WeaponInfo")
	float LifeTime = 5.0f;

private:
	FVector FireDirection;

	UFUNCTION()
	void OnPersonHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;
};