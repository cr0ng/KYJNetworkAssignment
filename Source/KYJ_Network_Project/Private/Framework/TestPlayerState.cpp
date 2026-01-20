// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Character/PlayerCharacter.h"
#include "UI/GameHUD.h"
#include "UI/ScoreWidget.h"

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
 /*   APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    AGameHUD* HUD = PC->GetHUD<AGameHUD>();
    if (!HUD) return;*/

    // 이 PlayerState가 로컬 플레이어 것인가?
    //if (PC->PlayerState == this)
    //{
    //    // 내 점수
    //    if (HUD->MyScoreText)
    //    {
    //        HUD->MyScoreText->UpdateScore(MyScore);
    //    }
    //}
    //else
    //{
    //    // 상대 점수
    //    if (HUD->EnemyScoreText)
    //    {
    //        HUD->EnemyScoreText->UpdateScore(MyScore);
    //    }
    //}

	UE_LOG(LogTemp, Log, TEXT("[%d]Score : %d"), GetPlayerId(), MyScore);
	if (!ScoreHud.IsValid())
	{
		if (GetPlayerController())
		{
			UE_LOG(LogTemp, Log, TEXT("플레이어 컨트롤러 있음"));
			AGameHUD* HUD = GetPlayerController()->GetHUD<AGameHUD>();
			if (HUD && HUD->GetScoreWidget().IsValid())
			{
				UE_LOG(LogTemp, Log, TEXT("HUD와 HUD위젯도 있음"));
				ScoreHud = Cast<UScoreWidget>(HUD->GetScoreWidget().Get());
			}
		}
	}
	if (ScoreHud.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("ScoreHud 있음"));
		ScoreHud->UpdateScore(MyScore);
	}
}
