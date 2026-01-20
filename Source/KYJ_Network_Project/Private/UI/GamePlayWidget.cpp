// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GamePlayWidget.h"
#include "UI/ScoreWidget.h"
#include "Framework/TestGameStateBase.h"
#include "Framework/TestPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UGamePlayWidget::UpdateScore(int32 NewScore)
{
    MyScoreText->UpdateIntValue(NewScore);

 //   UE_LOG(LogTemp,Log,TEXT("UpdateScore()"))
 //   if (!CachedGameState.IsValid() || !CachedGameState->IsGameOver())
 //   {
 //       ResultText->SetVisibility(ESlateVisibility::Hidden);
 //       return;
 //   }

 //   // 자기 PlayerState 가져오기
 //   APlayerController* PC = GetOwningPlayer();
 //   if (!PC) return;

 //   ATestPlayerState* MyPS = PC->GetPlayerState<ATestPlayerState>();
 //   if (!MyPS) return;

 //   ATestGameStateBase* GS = CachedGameState.Get();
 //   if (!GS) return;

 //   int32 MyScore = MyPS->MyScore;
 //   int32 OtherScore = -1;

 //   for (APlayerState* PS : GS->PlayerArray)
 //   {
 //       if (ATestPlayerState* TPS = Cast<ATestPlayerState>(PS))
 //       {
 //           if (TPS != MyPS)
 //           {
 //               OtherScore = TPS->MyScore;
 //               break;
 //           }
 //       }
 //   }

	//MyScoreText->UpdateIntValue(MyScore);
 //   EnemyScoreText->UpdateIntValue(OtherScore);
}

void UGamePlayWidget::UpdateScoreHUD()
{
    int32 MyScore = 0;
    int32 OtherScore = 0;

    // 1️⃣ 내 PlayerState
    if (ATestPlayerState* MyPS = GetOwningPlayer()->GetPlayerState<ATestPlayerState>())
    {
        MyScore = MyPS->GetMyScore();
    }

    // 2️⃣ 상대 PlayerState (2인용 가정)
    if (AGameStateBase* GS = GetWorld()->GetGameState())
    {
        for (APlayerState* PS : GS->PlayerArray)
        {
            if (ATestPlayerState* TPS = Cast<ATestPlayerState>(PS))
            {
                if (TPS != GetOwningPlayer()->GetPlayerState<ATestPlayerState>())
                {
                    OtherScore = TPS->GetMyScore();
                    break; // 2인용이면 첫 번째 다른 플레이어
                }
            }
        }
    }

    // 3️⃣ HUD 갱신
    OnScoreChanged(MyScore, OtherScore);
}

void UGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ResultText->SetVisibility(ESlateVisibility::Hidden);

    UpdateScoreHUD();

	//if (ATestPlayerState* PS = GetOwningPlayer()->GetPlayerState<ATestPlayerState>())
	//{
	//	PS->OnMyScoreChanged.AddUObject(
	//		this, &UGamePlayWidget::OnScoreChanged);

	//	// 초기값 반영
	//	OnMScoreChanged(PS->GetMyScore());
	//}
}

void UGamePlayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ATestGameStateBase>(UGameplayStatics::GetGameState(this));
	}
	UpdateTimeDisplay();
	UpdateGameOverDisplay();

}

void UGamePlayWidget::UpdateTimeDisplay()
{
	if (CachedGameState.IsValid())
	{
		int32 Total = FMath::FloorToInt(CachedGameState->GetGameRemainingTime());
		int32 Minutes = Total / 60;
		int32 Seconds = Total % 60;
		RemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));

	}
}

void UGamePlayWidget::UpdateGameOverDisplay()
{
	//if (CachedGameState.IsValid() && CachedGameState->IsGameOver())
	//{
	//	ResultText->SetVisibility(ESlateVisibility::HitTestInvisible);
	//}
	//else
	//{
	//	ResultText->SetVisibility(ESlateVisibility::Hidden);
	//}

    if (!CachedGameState.IsValid() || !CachedGameState->IsGameOver())
    {
        ResultText->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    // 자기 PlayerState 가져오기
    APlayerController* PC = GetOwningPlayer();
    if (!PC) return;

    ATestPlayerState* MyPS = PC->GetPlayerState<ATestPlayerState>();
    if (!MyPS) return;

    ATestGameStateBase* GS = CachedGameState.Get();
    if (!GS) return;

    int32 MyScore = MyPS->MyScore;
    int32 OtherScore = -1;

    for (APlayerState* PS : GS->PlayerArray)
    {
        if (ATestPlayerState* TPS = Cast<ATestPlayerState>(PS))
        {
            if (TPS != MyPS)
            {
                OtherScore = TPS->MyScore;
                break;
            }
        }
    }

    FString ResultString;
    if (OtherScore == -1)
    {
        ResultString = TEXT("플레이어 정보 없음");
    }
    else if (MyScore > OtherScore)
    {
        ResultString = TEXT("승리!");
    }
    else if (MyScore < OtherScore)
    {
        ResultString = TEXT("패배!");
    }
    else
    {
        ResultString = TEXT("무승부!");
    }

    ResultText->SetText(FText::FromString(ResultString));
    ResultText->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UGamePlayWidget::OnScoreChanged(int32 MyScore, int32 OtherScore)
{
	MyScoreText->UpdateIntValue(MyScore);
	EnemyScoreText->UpdateIntValue(OtherScore);
}