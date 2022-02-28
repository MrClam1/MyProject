// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUserWidget.h"

FCharacterMainData UMainUserWidget::GetPlayerCharacterInfo() const
{
	FCharacterMainData PlayerInfo;
	PlayerInfo.Level = -1;
	const auto PlayerCharacter = GetOwningPlayerPawn();
	if (!PlayerCharacter) return PlayerInfo;
	const auto MainPlayer = Cast<AMainCharacterMag>(PlayerCharacter);
	if (!MainPlayer) return PlayerInfo;

	PlayerInfo = MainPlayer->GetCharacterMainData();

	return PlayerInfo;
}
