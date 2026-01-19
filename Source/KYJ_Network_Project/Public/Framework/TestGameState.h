// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TestGameState.generated.h"

/**
 * 
 */
UCLASS()
class KYJ_NETWORK_PROJECT_API ATestGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ATestGameState();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	inline float GetGameRemainingTime() const { return GameRemainingTime; }
	inline bool IsGameOver() const { return bGameOver; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
	float GameDuration = 60.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameRemainingTime = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	bool bGameOver = false;
};
