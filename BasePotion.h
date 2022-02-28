#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"

#include "Kismet/GameplayStatics.h"

#include "BasePotion.generated.h"

UCLASS()
class MYPROJECT_API ABasePotion : public ABaseItem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void HealthActiveItem();
	UFUNCTION(BlueprintCallable)
	void ManaActiveItem();
	UFUNCTION(BlueprintCallable)
	void StreightActiveItem();
	UFUNCTION(BlueprintCallable)
	void AgilityActiveItem();
	UFUNCTION(BlueprintCallable)
	void IntellectActiveItem();
	UFUNCTION(BlueprintCallable)
	int32 GetManaPotion() { return Mana; };
	UFUNCTION(BlueprintCallable)
	int32 GetStreightPotion() { return Streight; };
	UFUNCTION(BlueprintCallable)
	int32 GetAgilityPotion() { return Agility; };
	UFUNCTION(BlueprintCallable)
	int32 GetIntellectPotion() { return Intellect; };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PotionStatus")
	int32 Health = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PotionStatus")
	int32 Mana = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PotionStatus")
	int32 Streight = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PotionStatus")
	int32 Agility = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PotionStatus")
	int32 Intellect = 0;
};
