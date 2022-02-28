// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFood.h"

void ABaseFood::HealthFoodItem()
{
	if (!GetWorld()) return;
	Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddHealth(Health);
}