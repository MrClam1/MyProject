// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyProject/MyPlayerController.h"
#include "MyProject/MainCharacterMag.h"
#include "MyProject/MyHUD.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMainCharacterMag::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}

void AMyGameModeBase::ChangeLevel()
{
	switch (CurrentLevel)
	{
	case 0:
		break;
	case 1:
		StartFirstLevel();
		break;
	case 2:
		StartSecondLevel();
		break;
	default:
		break;
	}
}

// === [ 1 Level ] ===

void AMyGameModeBase::StartFirstLevel()
{

}




// === [ 2 Level ] ===

void AMyGameModeBase::StartSecondLevel()
{

}

void AMyGameModeBase::SpawnEnemy()
{
	/*
	UNavigationSystemV1* NavigationArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	FVector ResultSpawnLocation;
	if (!GetWorld()) return;
	const FVector ActorLoc = Cast<AMainCharacterMag>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetActorLocation();
	ResultSpawnLocation = NavigationArea->GetRandomReachablePointInRadius(GetWorld(), ActorLoc, 500.0f);
	
	AActor* EnemyRef = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyCharacterClass, ResultSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
	*/
}

void AMyGameModeBase::SpawnItem()
{
	if (!GetWorld()) return;
}