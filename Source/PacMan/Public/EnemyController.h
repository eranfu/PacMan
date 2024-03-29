// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
    void Possess(APawn* InPawn) override;
    void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
    void SearchNewPoint();

private:
    void GoHome();
    void ReArm();

    FTimerHandle DeadTimer;

    class AEnemy* Bot;
    FVector HomeLocation;
};
