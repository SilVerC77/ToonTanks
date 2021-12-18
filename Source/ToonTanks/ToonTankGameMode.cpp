// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankPlayerController.h"
#include "Tank.h"
#include "Tower.h"

AToonTankGameMode::AToonTankGameMode() {
	StartDelay = 3.f;
	TargetTowers = 0;
}

void AToonTankGameMode::ActorDied(AActor* DeadActor) {
	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		if (ToonTankPlayerController) {
			ToonTankPlayerController->SetPlayerEnableState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) {
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers <= 0) {
			GameOver(true);
		}
	}
}

void AToonTankGameMode::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart() {
	TargetTowers = GetTargetTowerCount();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTankPlayerController) {
		ToonTankPlayerController->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnabletimerDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTankPlayerController::SetPlayerEnableState,
			true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnabletimerDelegate,
			StartDelay,
			false);
	}

}

int32 AToonTankGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}
