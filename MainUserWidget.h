#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacterMag.h"
#include "MainUserWidget.generated.h"

UCLASS()
class MYPROJECT_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	FCharacterMainData GetPlayerCharacterInfo() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeMissionStatus(bool StatusBoolen);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeInventoryStatus(bool StatusBoolen);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeExp(int32 Level, float Experience);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeHealth(float Health, float MaxHealth);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeMana(float Mana, float MaxMana);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeSkills();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeRegen(float RegenHealth, float RegenMana);
	
};
