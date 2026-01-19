// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Character/PlayerCharacter.h"

void ATestPlayerState::AddScore(int32 Point)
{
	if (HasAuthority())
	{
		MyScore += Point;
		OnRep_MyScore();
		UE_LOG(LogTemp, Log, TEXT("점수 : %d"), MyScore);
	}
}

void ATestPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestPlayerState, MyScore);
}

void ATestPlayerState::OnRep_MyScore()
{
	// 허드나 위젯 만들고 추가하기
}
