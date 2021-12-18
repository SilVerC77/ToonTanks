// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

class ATank;
class AToonTankPlayerController;

/**
 *
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AToonTankGameMode();

	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool bWonGame);

protected:
	virtual void BeginPlay() override;

private:
	ATank* Tank;
	AToonTankPlayerController* ToonTankPlayerController;

	float StartDelay;

	void HandleGameStart();

	int32 TargetTowers;
	int32 GetTargetTowerCount();
};
