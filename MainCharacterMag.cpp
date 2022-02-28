
#include "MainCharacterMag.h"

AMainCharacterMag::AMainCharacterMag()
{
	PrimaryActorTick.bCanEverTick = true;

	/*

	MyMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MyMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MyMeshAsset(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon'"));
	if (MyMeshAsset.Succeeded())
	{
		MyMeshComponent->SetSkeletalMesh(MyMeshAsset.Object);
		MyMeshComponent->SetRelativeTransform(FTransform(FRotator(0.0f, -90.0f, 0.0f), FVector(0.0f, 0.0f, -70.0f), FVector(0.75f, 0.75f, 0.75f)));
	}
	MyArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	MyArrowComponent->SetupAttachment(MyMeshComponent);

	*/

	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	MySpringArm->SetupAttachment(RootComponent);
	MySpringArm->TargetArmLength = 100.0f;
	//MySpringArm->SetRelativeTransform(FTransform(FRotator(338.3f, 0.0f, 0.0f), FVector(0.0f, 40.0f, 50.0f), FVector(1.0f, 1.0f, 1.0f)));
	MySpringArm->bUsePawnControlRotation = true;
	MySpringArm->SetRelativeRotation(FRotator(338.3f, 0.0f, 0.0f));

	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	MyCameraComponent->SetupAttachment(MySpringArm);
	MyCameraComponent->SetRelativeLocation(FVector(0.0f, 40.0f, 50.0f));

}

void AMainCharacterMag::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AMainCharacterMag::OnTakeDamageHandle);
}

void AMainCharacterMag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	if (GetWorld() && !(CharacterMainData.Health == CharacterMainData.MaxHealth && CharacterMainData.Mana == CharacterMainData.MaxMana))
	{
		GetWorld()->GetTimerManager().SetTimer(FTimerRegen, this, &AMainCharacterMag::RegenCharacter, 1.0f, true);
	}
	*/
}

void AMainCharacterMag::RegenCharacter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Test")));
	CharacterMainData.Health = FMath::Min(CharacterMainData.Health + CharacterRegenHealth, CharacterMainData.MaxHealth);
	CharacterMainData.Mana = FMath::Min(CharacterMainData.Mana + CharacterRegenMana, CharacterMainData.MaxMana);
	OnHealthChanged.Broadcast(CharacterMainData.Health, CharacterMainData.MaxHealth);
	OnManaChanged.Broadcast(CharacterMainData.Mana, CharacterMainData.MaxMana);
}

void AMainCharacterMag::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis(TEXT("Action_Forward"), this, &AMainCharacterMag::Action_Forward);
		PlayerInputComponent->BindAxis(TEXT("Action_Right"), this, &AMainCharacterMag::Action_Right);
		PlayerInputComponent->BindAxis(TEXT("Action_LookUp"), this, &AMainCharacterMag::AddControllerPitchInput);
		PlayerInputComponent->BindAxis(TEXT("Action_LookAround"), this, &AMainCharacterMag::AddControllerYawInput);

		PlayerInputComponent->BindAction(TEXT("Action_Ability"), IE_Pressed, this, &AMainCharacterMag::Action_Ability);
		PlayerInputComponent->BindAction(TEXT("Action_Mission"), IE_Pressed, this, &AMainCharacterMag::Action_ShowMission);
		PlayerInputComponent->BindAction(TEXT("Action_Ability_Ult"), IE_Pressed, this, &AMainCharacterMag::Action_Ability_Ult);
		PlayerInputComponent->BindAction(TEXT("Action_Inventory"), IE_Pressed, this, &AMainCharacterMag::Action_ChangeInventory);
		PlayerInputComponent->BindAction(TEXT("Action_Jump"), IE_Pressed, this, &AMainCharacterMag::Jump);
		PlayerInputComponent->BindAction(TEXT("Action_Jump"), IE_Released, this, &AMainCharacterMag::StopJumping);
		PlayerInputComponent->BindAction(TEXT("Action_Fire"), IE_Pressed, this, &AMainCharacterMag::Action_Fire);
		PlayerInputComponent->BindAction(TEXT("Action_Run"), IE_Pressed, this, &AMainCharacterMag::Action_Run);
		PlayerInputComponent->BindAction(TEXT("Action_Run"), IE_Released, this, &AMainCharacterMag::StopAction_Run);
	}
}

void AMainCharacterMag::Action_ShowMission()
{
	isOpenMissionBoolen = !isOpenMission();
	OnMissionChanges.Broadcast();
}

void AMainCharacterMag::Action_ChangeInventory()
{
	isOpenInventoryBoolen = !isOpenInventory();
	OnInventoryChanges.Broadcast();
}

void AMainCharacterMag::Action_Forward(float AxisValue)
{
	if (CharacterData.isDead != true && CharacterData.Talking != true)
	{
		AddMovementInput(GetActorForwardVector(), AxisValue * CharacterMainData.Speed);
	}
}

void AMainCharacterMag::Action_Right(float AxisValue)
{
	if (CharacterData.isDead != true && CharacterData.Talking != true)
	{
		AddMovementInput(GetActorRightVector(), AxisValue * CharacterMainData.Speed);
	}
}

void AMainCharacterMag::Action_Fire()
{
	CharacterData.isAttacking = true;

	AnimBlueprint(CharacterData.AttackCount);
	switch (CharacterData.AttackCount)
	{
	case 0:
		CharacterData.AttackCount = 1;
		break;
	case 1:
		CharacterData.AttackCount = 2;
		break;
	case 2:
		CharacterData.AttackCount = 0;
		break;
	}
	MakeShot();
}

void AMainCharacterMag::Action_Run()
{

}

void AMainCharacterMag::StopAction_Run()
{

}

void AMainCharacterMag::MakeShot()
{

	FVector SpawnVector = GetActorLocation() + (GetActorForwardVector() * 40.0f);
	const FTransform SpawnTransform(FRotator::ZeroRotator, SpawnVector);
	FVector ViewLocation;
	FRotator ViewRotator;

	const auto PlayerController = GetController<APlayerController>();
	if (!PlayerController) return;
	PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotator);

	const FVector TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotator.Vector();
	const FVector TraceEnd = TraceStart + ShootDirection * 1000.0f;
	
	FHitResult HitResult;
	FCollisionQueryParams CollusionParams;
	CollusionParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(HitResult, SpawnVector, TraceEnd, ECollisionChannel::ECC_Visibility, CollusionParams);
	//DrawDebugLine(GetWorld(), SpawnVector, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);

	const FVector TargetFound = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (TargetFound - GetActorLocation()).GetSafeNormal();

	AMyWeaponMag* MyWeaponMag = GetWorld()->SpawnActorDeferred<AMyWeaponMag>(MyWeaponMagClass, SpawnTransform);
	if (MyWeaponMag)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Output: %s"), *Direction.ToString()));
		MyWeaponMag->SetFireDirection(Direction);
		MyWeaponMag->SetOwner(GetOwner());
		MyWeaponMag->FinishSpawning(SpawnTransform);
	}

}

void AMainCharacterMag::SetCharacterInfo(int32 Strenght, int32 Agility, int32 Intellect)
{
	CharacterMainData.Strength = Strenght;
	CharacterMainData.Agility = Agility;
	CharacterMainData.Intellect = Intellect;

	GetStartCharacterInfo();
}

void AMainCharacterMag::GetStartCharacterInfo()
{
	check(CharacterMainData.Strength > 0);
	check(CharacterMainData.Agility > 0);
	check(CharacterMainData.Intellect > 0);
	check(CharacterMainData.Level > 0);

	CharacterMainData.MaxHealth = (CharacterMainData.Strength * CharacterMainData.Level) * 100;
	CharacterMainData.Health = CharacterMainData.MaxHealth;
	CharacterMainData.MaxMana = (CharacterMainData.Intellect * CharacterMainData.Level) * 100;
	CharacterMainData.Mana = CharacterMainData.MaxMana;
	CharacterMainData.Damage = CharacterMainData.Strength * CharacterMainData.Level * 20.0f;
	CharacterMainData.Speed = CharacterMainData.Agility * 50;
	CharacterMainData.MaxExperience = CharacterMainData.Level * CharacterMainData.Level * 100.0f;

	CharacterRegenHealth = (CharacterMainData.Strength * 0.001) * CharacterMainData.MaxHealth * CharacterMainData.Level;
	CharacterRegenMana = (CharacterMainData.Intellect * 0.001) * CharacterMainData.MaxMana * CharacterMainData.Level;

	OnRegenChanged.Broadcast(CharacterRegenHealth, CharacterRegenMana);
}

void AMainCharacterMag::Action_Ability()
{
	if (CharacterMainData.Mana < 50.0f)
	{
		OnNoneMana();
		return;
	}

	if (isAbilityActive == false && GetWorld())
	{
		isAbilityActive = true;
		HealthModifier();
		CharacterMainData.Mana = CharacterMainData.Mana - 50.0f;
		//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("%f"), TimeAbility));
		OnAbilityFirst(TimeAbility);
		GetWorld()->GetTimerManager().SetTimer(FResetTimerHealth, this, &AMainCharacterMag::ResetAbility, TimeAbility, false);
	}
}

void AMainCharacterMag::ResetAbility()
{
	isAbilityActive = false;
}

void AMainCharacterMag::ResetUlt()
{
	isAbilityUltActive = false;
}

void AMainCharacterMag::Action_Ability_Ult()
{
	if (CharacterMainData.Mana < 200.0f)
	{
		OnNoneMana();
		return;
	}
	if (isAbilityUltActive == false && GetWorld())
	{
		isAbilityUltActive = true;
		UGameplayStatics::ApplyRadialDamage(GetWorld(), CharacterMainData.Damage, GetActorLocation(), 400.0f, UDamageType::StaticClass(), { GetOwner() }, this, GetController(), false);
		TArray<FHitResult> HitResultArray;
		//UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 400.0f, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), false, {}, EDrawDebugTrace::None, HitResultArray, true);
		
		bool isHit = GetWorld()->SweepMultiByChannel(HitResultArray, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECC_WorldStatic, FCollisionShape::MakeSphere(400.0f));

		OnAbilitySecond(TimeAbilityUlt);
		GetWorld()->GetTimerManager().SetTimer(FResetTimerUlt, this, &AMainCharacterMag::ResetUlt, TimeAbilityUlt, false);

		if (isHit)
		{
			for (const FHitResult HitResult : HitResultArray)
			{
				AActor* Test = HitResult.GetActor();
				//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("%s"), *(Test->GetClass()->GetName())));
				if (HitResult.GetActor()->GetClass()->GetName() == "MyEnemyCharacter_C")
				{
					//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Test")));
					Cast<AEnemyCharacter>(Test)->SetCharacterStun(5.0f);
				}

				//Cast<AEnemyCharacter>(HitResult.GetActor())->SetCharacterStun(5.0f);
			}
			CharacterMainData.Mana = CharacterMainData.Mana - 200.0f;
		}
	}
}

void AMainCharacterMag::HealthModifier()
{
	//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("HelloWorld")));
	CharacterMainData.Health = FMath::Min(CharacterMainData.Health + CharacterMainData.MaxHealth * HealthRegenPercent, CharacterMainData.MaxHealth);
	OnHealthChanged.Broadcast(CharacterMainData.Health, CharacterMainData.MaxHealth);
}

void AMainCharacterMag::NewExp(float Experience)
{
	if (CharacterMainData.Experience + Experience >= CharacterMainData.MaxExperience)
	{
		CharacterMainData.Experience = CharacterMainData.Experience + Experience;
		bool new_exp = true;
		while (new_exp == true)
		{
			if (CharacterMainData.Experience >= CharacterMainData.MaxExperience)
			{
				CharacterMainData.Experience = CharacterMainData.Experience - CharacterMainData.MaxExperience;
				CharacterMainData.Level = CharacterMainData.Level + 1;
				CharacterMainData.MaxExperience = CharacterMainData.Level * CharacterMainData.Level * 100.0f;
				UpdateLevel();
			}
			else {
				new_exp = false;
			}
		}
	}
	else
	{
		CharacterMainData.Experience = CharacterMainData.Experience + Experience;
	}

	OnLevelChanged.Broadcast(CharacterMainData.Experience / CharacterMainData.MaxExperience, CharacterMainData.Level);
}

void AMainCharacterMag::UpdateLevel()
{
	CharacterMainData.MaxHealth = (CharacterMainData.Strength * CharacterMainData.Level) * 100;
	CharacterMainData.MaxMana = (CharacterMainData.Intellect * CharacterMainData.Level) * 100;
	CharacterMainData.Damage = CharacterMainData.Strength * CharacterMainData.Level * 20.0f;
	CharacterMainData.Speed = CharacterMainData.Agility * 50;
	OnSkillsChanges.Broadcast();

	CharacterRegenHealth = (CharacterMainData.Strength * 0.001) * CharacterMainData.MaxHealth * CharacterMainData.Level;
	CharacterRegenMana = (CharacterMainData.Intellect * 0.001) * CharacterMainData.MaxMana * CharacterMainData.Level;
	OnRegenChanged.Broadcast(CharacterRegenHealth, CharacterRegenMana);
}

void AMainCharacterMag::OnTakeDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0 || isDead()) return;
	CharacterMainData.Health = FMath::Clamp(CharacterMainData.Health - Damage, 0.0f, CharacterMainData.MaxHealth);
	OnHealthChanged.Broadcast(CharacterMainData.Health, CharacterMainData.MaxHealth);
	if (CharacterMainData.Health == 0) SetCharacterDied();
}

void AMainCharacterMag::SetCharacterDied()
{
	GetCharacterMovement()->DisableMovement();
	if (!DeathAnimation) return;
	GetMesh()->PlayAnimation(DeathAnimation, false);
	SetLifeSpan(3.0f);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AMainCharacterMag::ChangeCharacterSkill()
{
	CharacterMainData.MaxHealth = (CharacterMainData.Strength * CharacterMainData.Level) * 100;
	CharacterMainData.MaxMana = (CharacterMainData.Intellect * CharacterMainData.Level) * 100;
	CharacterMainData.Damage = CharacterMainData.Strength * CharacterMainData.Level * 20.0f;
	CharacterMainData.Speed = CharacterMainData.Agility * 50;
	CharacterRegenHealth = (CharacterMainData.Strength * 0.001) * CharacterMainData.MaxHealth * CharacterMainData.Level;
	CharacterRegenMana = (CharacterMainData.Intellect * 0.001) * CharacterMainData.MaxMana * CharacterMainData.Level;
}

// Change Character Status //

void AMainCharacterMag::AddHealth(int32 Health)
{
	CharacterMainData.Health = FMath::Min(CharacterMainData.Health + Health, CharacterMainData.MaxHealth);
	OnHealthChanged.Broadcast(CharacterMainData.Health, CharacterMainData.MaxHealth);
}

void AMainCharacterMag::AddMana(int32 Mana)
{
	CharacterMainData.Health = FMath::Min(CharacterMainData.Health + Mana, CharacterMainData.MaxHealth);
	OnManaChanged.Broadcast(CharacterMainData.Mana, CharacterMainData.MaxMana);
}

void AMainCharacterMag::AddStrenght(int32 Strenght)
{
	CharacterMainData.Strength += Strenght;
	ChangeCharacterSkill();
	OnSkillsChanges.Broadcast();
}

void AMainCharacterMag::AddAgility(int32 Agility)
{
	CharacterMainData.Agility += Agility;
	ChangeCharacterSkill();
	OnSkillsChanges.Broadcast();
}

void AMainCharacterMag::AddIntellect(int32 Intellect)
{
	CharacterMainData.Intellect += Intellect;
	ChangeCharacterSkill();
	OnSkillsChanges.Broadcast();
}

