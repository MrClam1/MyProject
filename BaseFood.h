
#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"

#include "Engine/Texture2D.h"

#include "Kismet/GameplayStatics.h"

#include "BaseFood.generated.h"

UCLASS()
class MYPROJECT_API ABaseFood : public ABaseItem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void HealthFoodItem();
	UFUNCTION(BlueprintCallable)
	int32 GetHealthFood() { return Health; };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FoodStatus")
	int32 Health = 0;
};
