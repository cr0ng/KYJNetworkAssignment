// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Character/PlayerCharacter.h"
#include "UI/GameHUD.h"
#include "UI/ScoreWidget.h"
#include "UI/GamePlayWidget.h"
#include "Framework/TestGameStateBase.h"

void ATestPlayerState::AddScore(int32 Point)
{
	/*if (HasAuthority())
	{
		MyScore += Point;
		OnRep_MyScore();
		UE_LOG(LogTemp, Log, TEXT("점수 : %d"), MyScore);
	}*/

    if (HasAuthority())
    {
        MyScore += Point;
        OnRep_MyScore();

        // 서버에서 모든 PlayerState 확인
        if (AGameStateBase* GS = GetWorld()->GetGameState())
        {
            for (APlayerState* PS : GS->PlayerArray)
            {
                if (ATestPlayerState* TPS = Cast<ATestPlayerState>(PS))
                {
                    UE_LOG(LogTemp, Log, TEXT("%s의 점수 : %d"), *TPS->GetPlayerName(), TPS->MyScore);
                }
            }
        }
    }
}

void ATestPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestPlayerState, MyScore);
}

void ATestPlayerState::OnRep_MyScore()
{

	//if (!ScoreHud.IsValid())
	//{
	//	if (GetPlayerController())
	//	{
	//		//UE_LOG(LogTemp, Log, TEXT("플레이어 컨트롤러 있음"));
	//		AGameHUD* HUD = GetPlayerController()->GetHUD<AGameHUD>();
	//		if (HUD && HUD->GetGameplayWidget().IsValid())
	//		{
	//			//UE_LOG(LogTemp, Log, TEXT("HUD와 HUD위젯도 있음"));
	//			ScoreHud = Cast<UGamePlayWidget>(HUD->GetGameplayWidget().Get());
	//		}
	//	}
	//}
	//if (ScoreHud.IsValid())
	//{
	//	ScoreHud->UpdateScore(MyScore);
	//}

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (AGameHUD* HUD = PC->GetHUD<AGameHUD>())
		{
			if (HUD->GetGameplayWidget().IsValid())
			{
				if (UGamePlayWidget* GPW =
					Cast<UGamePlayWidget>(HUD->GetGameplayWidget().Get()))
				{
					GPW->RefreshScores();
				}
			}
		}
	}
}
