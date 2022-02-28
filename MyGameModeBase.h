#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

#include "MyGameModeBase.generated.h"

class AEnemyCharacter;

UCLASS()
class MYPROJECT_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentLevel(int32 CountLevel) { CurrentLevel = CountLevel; ChangeLevel(); };
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentLevel() { return CurrentLevel; };
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
	UFUNCTION(BlueprintCallable)
	void SpawnItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AEnemyCharacter> EnemyCharacterClass;

private:

	int32 CurrentLevel = 0;
	void ChangeLevel();
	void StartFirstLevel();
	void StartSecondLevel();
};
