#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Engine/Player.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"

#include "GameplayTagContainer.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "MyProject/MyWeaponMag.h"
#include "MyProject/EnemyCharacter.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

#include "DrawDebugHelpers.h"
#include "MainCharacterMag.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeMainCharacterHealth, float, CharacterHealth, float, CharacterMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeMainCharacterMana, float, CharacterMana, float, CharacterMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeMainCharacterRegen, float, CharacterRegenHealth, float, CharacterRegenMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeMainCharacterLevel, float, CharacterExperience, int32, CharacterLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeCharacterSkills);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeCharacterInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeCharacterMission);

class AMyWeaponMag;

//Структура FCharacterInventory - инвентарь героя

//Структура FCharacterDataStatus - статус героя
USTRUCT(BlueprintType)
struct FCharacterDataStatus
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	bool Talking = false;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	bool isDead = false;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	bool isAttacking = false;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	int32 AttackCount = 0;
};

//Структура FCharacterMainData - показатели героя
USTRUCT(BlueprintType)
struct FCharacterMainData
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
	float MaxExperience = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	int32 Level = 1;

};

UCLASS()
class MYPROJECT_API AMainCharacterMag : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacterMag();

	// === //

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MyComponents")
	USkeletalMeshComponent* MyMeshComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MyComponents")
	USpringArmComponent* MySpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MyComponents")
	UCameraComponent* MyCameraComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MyComponents")
	UArrowComponent* MyArrowComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	FCharacterDataStatus CharacterData;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	FCharacterMainData CharacterMainData;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float TimeAbility = 10.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float HealthRegenPercent = 0.1f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float TimeAbilityUlt = 20.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float CharacterHealth;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float CharacterMaxHealth;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float CharacterMana;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float CharacterMaxMana;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float CharacterExperience;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float CharacterLevel;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float CharacterRegenHealth;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterStatus")
	float CharacterRegenMana;
	UPROPERTY(BlueprintAssignable)
	FChangeMainCharacterHealth OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FChangeMainCharacterMana OnManaChanged;
	UPROPERTY(BlueprintAssignable)
	FChangeMainCharacterLevel OnLevelChanged;
	UPROPERTY(BlueprintAssignable)
	FChangeMainCharacterRegen OnRegenChanged;
	UPROPERTY(BlueprintAssignable)
	FChangeCharacterSkills OnSkillsChanges;
	UPROPERTY(BlueprintAssignable)
	FChangeCharacterInventory OnInventoryChanges;
	UPROPERTY(BlueprintAssignable)
	FChangeCharacterMission OnMissionChanges;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimationAsset* DeathAnimation;


	// === //

	UFUNCTION()
	void OnTakeDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnNoneMana();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AnimBlueprint(int32 ID_Anim);
	UFUNCTION(BlueprintCallable)
	void SetCharacterInfo(int32 Strenght, int32 Agility, int32 Intellect);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAbilityFirst(float Timer);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAbilitySecond(float Timer);
	UFUNCTION(BlueprintCallable)
	bool isDead() { return CharacterMainData.Health == 0; };
	UFUNCTION(BlueprintCallable)
	bool isOpenInventory() { return isOpenInventoryBoolen; };
	UFUNCTION(BlueprintCallable)
	bool isOpenMission() { return isOpenMissionBoolen; };
	UFUNCTION(BlueprintCallable)
	void RegenCharacter();

	// Change Character Status //

	UFUNCTION(BlueprintCallable)
	void AddHealth(int32 Health);
	UFUNCTION(BlueprintCallable)
	void AddMana(int32 Mana);
	UFUNCTION(BlueprintCallable)
	void AddStrenght(int32 Strenght);
	UFUNCTION(BlueprintCallable)
	void AddAgility(int32 Agility);
	UFUNCTION(BlueprintCallable)
	void AddIntellect(int32 Intellect);


	// === //

	FCharacterMainData GetCharacterMainData() { return CharacterMainData; };

protected:
	virtual void BeginPlay() override;

	void Action_Forward(float AxisValue);
	void Action_Right(float AxisValue);
	void Action_ChangeInventory();
	void Action_Run();
	void StopAction_Run();
	void Action_Fire();
	void Action_Ability();
	void Action_Ability_Ult();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AMyWeaponMag> MyWeaponMagClass;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MakeShot();
	void NewExp(float Experience);

private:
	void GetStartCharacterInfo();
	void HealthModifier();
	void ResetAbility();
	void ResetUlt();
	void UpdateLevel();
	void SetCharacterDied();
	void ChangeCharacterSkill();
	void Action_ShowMission();

	FTimerHandle FTimerRegen;
	FTimerHandle FResetTimerHealth;
	FTimerHandle FResetTimerUlt;
	bool isAbilityActive = false;
	bool isAbilityUltActive = false;
	bool isOpenInventoryBoolen = false;
	bool isOpenMissionBoolen = false;
	
};

