#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Engine/Player.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/World.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameplayTagContainer.h"
#include "Kismet/GameplayStatics.h"
#include "Delegates/Delegate.h"

#include "MyProject/MyWeaponMag.h"
#include "MyProject/MyPlayerController.h"

#include "Runtime/Engine/Public/EngineGlobals.h"

#include "DrawDebugHelpers.h"
#include "EnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeEnemyDead);

USTRUCT(BlueprintType)
struct FEnemyMainData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float Health = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float MaxHealth = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float Mana = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float MaxMana = 0.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CharacterStatus")
	int32 Strength = 0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CharacterStatus")
	int32 Agility = 0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CharacterStatus")
	int32 Intellect = 0;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float Damage = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float Speed = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float Experience = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	int32 Level = 1;

};

UCLASS()
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	FEnemyMainData EnemyMainData;
	UFUNCTION(BlueprintCallable)
	void GetMainData(int32 Strenght, int32 Agility, int32 Intellect, int32 Level);
	UFUNCTION()
	void OnTakeEnemyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(BlueprintCallable)
	FEnemyMainData GetEnemyData() { return EnemyMainData;  };
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DeathDrop();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeEnemyHealth(float Health, float MaxHealth);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeEnemyMana(float Mana, float MaxMana);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAttackAnimation();
	UFUNCTION(BlueprintCallable)
	void SetCharacterStun(float Time);
	UFUNCTION(BlueprintCallable)
	void FoundCharacter(AActor* PlayerActor);
	UFUNCTION(BlueprintCallable)
	void RemoveCharacterStun();
	UFUNCTION(BlueprintCallable)
	bool isDead() { return EnemyMainData.Health == 0; };
	UFUNCTION(BlueprintCallAble)
	bool isAvailbleAbility() { return isAbility; }
	UFUNCTION(BlueprintCallable)
	bool isAvailbleUltAbility() { return isUltAbility; }
	UFUNCTION(BlueprintCallable)
	void OnAttackAbility();
	UFUNCTION(BlueprintCallable)
	void OnAttackUltAbility();
	UPROPERTY(BlueprintAssignable)
	FChangeEnemyDead OnEnemyDied;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimationAsset* DeathAnimation;

private:
	float TimerAbility = 8.0f;
	float TimerUltAbility = 20.0f;
	bool isAbility = true;
	bool isUltAbility = true;
	FTimerHandle FTimerStun;
	FTimerHandle FTimerAttack;
	FTimerHandle FTimerAbility;
	FTimerHandle FTimerUltAbility;
	bool FoundCharacterBool = false;
	AActor* PlayerTarget;

	void SetMainData();
	void SetEnemyDied(AActor* PlayerActor);
	void AttackCharacter();
	void ResetAbility();
	void ResetUltAbility();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
