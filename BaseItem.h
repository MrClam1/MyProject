// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyProject/MainCharacterMag.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Class.h"
#include "BaseItem.generated.h"

class USphereComponent;

UENUM(BlueprintType)
enum class ECharacterAdd : uint8 {
	VE_Health			UMETA(DisplayName = "Health"),
	VE_Mana				UMETA(DisplayName = "Mana"),
	VE_Strenght			UMETA(DisplayName = "Strenght"),
	VE_Agility			UMETA(DisplayName = "Agility"),
	VE_Intellect		UMETA(DisplayName = "Intellect"),
};

UCLASS()
class MYPROJECT_API ABaseItem : public APawn
{
	GENERATED_BODY()

public:
	ABaseItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterAdd ItemAddCharacterBuff;

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIconItem() { return Icon; };
	UFUNCTION(BlueprintCallable)
	FString GetNameItem() { return Name; };
	UFUNCTION(BlueprintCallable)
	bool CanBeUse() { return isUsable; };
	UFUNCTION(BlueprintCallable)
	bool CanBeStacked() { return isStackable; };
	UFUNCTION(BlueprintCallable)
	void ActivateItem(int32 Count, ECharacterAdd Parametr);



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemStatus")
	FString Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemStatus")
	FString Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemStatus")
	bool isStackable = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemStatus")
	bool isUsable = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemStatus")
	UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemStatus")
	UStaticMesh* ModelItem;

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

};
