// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

//Forward Declaration
class ATank;
/**
 *
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
public:
	ATower();
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	virtual void BeginPlay()override;

private:
	ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRange;

	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRate;


	void CheckFireCondition();

	bool InFireRange();
};
