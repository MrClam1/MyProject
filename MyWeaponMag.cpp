
#include "MyWeaponMag.h"

AMyWeaponMag::AMyWeaponMag()
{

	PrimaryActorTick.bCanEverTick = false;
	CollusionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	CollusionComponent->InitSphereRadius(10.0f);
	CollusionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollusionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	SetRootComponent(CollusionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");


}

void AMyWeaponMag::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollusionComponent);
	MovementComponent->Velocity = FireDirection * MovementComponent->InitialSpeed;
	CollusionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollusionComponent->OnComponentHit.AddDynamic(this, &AMyWeaponMag::OnPersonHit);
	SetLifeSpan(LifeTime);
}

void AMyWeaponMag::OnPersonHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;
	MovementComponent->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, UDamageType::StaticClass(), { GetOwner() }, this, GetController(), bDoFullDamage);
	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, FColor::Red, false, 5.0f);
	Destroy();
}

AController* AMyWeaponMag::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

