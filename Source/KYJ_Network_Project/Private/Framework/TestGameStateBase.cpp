// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestGameStateBase.h"

#include "Net/UnrealNetwork.h"

ATestGameStateBase::ATestGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	GameRemainingTime = GameDuration;
}

void ATestGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && !bGameOver)
	{
		GameRemainingTime -= DeltaTime;
		if (GameRemainingTime <= 0.0f)
		{
			GameRemainingTime = 0.0f;
			bGameOver = true;

		}
	}
}

void ATestGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestGameStateBase, GameRemainingTime);
	DOREPLIFETIME(ATestGameStateBase, bGameOver);
}
