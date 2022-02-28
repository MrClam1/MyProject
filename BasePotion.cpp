// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePotion.h"

void ABasePotion::HealthActiveItem()
{
	if (!GetWorld()) return;
	Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddHealth(Health);
}

void ABasePotion::ManaActiveItem()
{
	if (!GetWorld()) return;
	Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddMana(Mana);
}

void ABasePotion::StreightActiveItem()
{
	if (!GetWorld()) return;
	Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddStrenght(Streight);
}

void ABasePotion::AgilityActiveItem()
{
	if (!GetWorld()) return;
	Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddAgility(Agility);
}

void ABasePotion::IntellectActiveItem()
{
	if (!GetWorld()) return;
	Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddIntellect(Intellect);
}