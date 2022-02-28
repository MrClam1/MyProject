#include "BaseItem.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseItem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseItem::ActivateItem(int32 Count, ECharacterAdd Parametr)
{
	if (!GetWorld()) return;
	switch (Parametr)
	{
	case ECharacterAdd::VE_Health:
		Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddHealth(Count);
		break;
	case ECharacterAdd::VE_Mana:
		Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddMana(Count);
		break;
	case ECharacterAdd::VE_Strenght:
		Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddStrenght(Count);
		break;
	case ECharacterAdd::VE_Agility:
		Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddAgility(Count);
		break;
	case ECharacterAdd::VE_Intellect:
		Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddIntellect(Count);
		break;
	}
}

