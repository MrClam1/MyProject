#include "EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &AEnemyCharacter::OnTakeEnemyDamageHandle);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FoundCharacterBool == true && GetWorld())
	{
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Distance: %f"), GetDistanceTo(PlayerTarget)));
		if (GetDistanceTo(PlayerTarget) <= 50.0f)
		{
			GetWorld()->GetTimerManager().SetTimer(FTimerAttack, this, &AEnemyCharacter::AttackCharacter, 1.0f, false);
		}
	}
}

void AEnemyCharacter::AttackCharacter()
{

}

void AEnemyCharacter::FoundCharacter(AActor* PlayerActor)
{
	if (!PlayerActor) return;
	PlayerTarget = PlayerActor;
	FoundCharacterBool = true;
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::SetMainData()
{
	check(EnemyMainData.Strength > 0);
	check(EnemyMainData.Agility > 0);
	check(EnemyMainData.Intellect > 0);
	check(EnemyMainData.Level > 0);

	EnemyMainData.MaxHealth = (EnemyMainData.Strength * EnemyMainData.Level) * 100;
	EnemyMainData.Health = EnemyMainData.MaxHealth;
	EnemyMainData.MaxMana = (EnemyMainData.Intellect * EnemyMainData.Level) * 100;
	EnemyMainData.Mana = EnemyMainData.MaxMana;
	EnemyMainData.Damage = EnemyMainData.Strength * EnemyMainData.Level * 20.0f;
	EnemyMainData.Speed = EnemyMainData.Agility * 50;
}

void AEnemyCharacter::GetMainData(int32 Strenght, int32 Agility, int32 Intellect, int32 Level)
{

	EnemyMainData.Strength = Strenght;
	EnemyMainData.Agility = Agility;
	EnemyMainData.Intellect = Intellect;
	EnemyMainData.Level = Level;

	SetMainData();
}

void AEnemyCharacter::OnTakeEnemyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, DamageCauser->GetOwner()->GetName());
	if (Damage <= 0 || isDead()) return;
	EnemyMainData.Health = FMath::Clamp(EnemyMainData.Health - Damage, 0.0f, EnemyMainData.MaxHealth);
	ChangeEnemyHealth(EnemyMainData.Health, EnemyMainData.MaxHealth);
	if (EnemyMainData.Health == 0) SetEnemyDied(DamageCauser->GetOwner());
}

void AEnemyCharacter::SetEnemyDied(AActor* PlayerActor)
{
	OnEnemyDied.Broadcast();
	GetCharacterMovement()->DisableMovement();
	if (!DeathAnimation) return;
	GetMesh()->PlayAnimation(DeathAnimation, false);
	Cast<AMyPlayerController>(PlayerActor)->EnemyWasKilled();
	SetLifeSpan(3.0f);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AEnemyCharacter::SetCharacterStun(float Time)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(FTimerStun, this, &AEnemyCharacter::RemoveCharacterStun, Time, false);
		GetCharacterMovement()->DisableMovement();
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Stun")));
	}
}

void AEnemyCharacter::RemoveCharacterStun()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AEnemyCharacter::OnAttackAbility()
{
	if (GetWorld() && isAvailbleAbility())
	{
		GetWorld()->GetTimerManager().SetTimer(FTimerAbility, this, &AEnemyCharacter::ResetAbility, TimerAbility, false);
	}
}

void AEnemyCharacter::ResetAbility()
{

}

void AEnemyCharacter::OnAttackUltAbility()
{
	if (GetWorld() && isAvailbleUltAbility())
	{
		GetWorld()->GetTimerManager().SetTimer(FTimerUltAbility, this, &AEnemyCharacter::ResetUltAbility, TimerUltAbility, false);
	}
}

void AEnemyCharacter::ResetUltAbility()
{

}

