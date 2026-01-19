// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"
#include "Components/TextBlock.h"
#include "Framework/TestPlayerState.h"

void UScoreWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UScoreWidget::UpdateScore(int32 NewScore)
{
    ScoreText->SetText(FText::AsNumber(NewScore));
}

//void UScoreWidget::UpdateScore(ATestPlayerState* LocalPS, ATestPlayerState* OtherPS)
//{
//    if (!LocalPS || !OtherPS) return;
//
//    MyScoreText->SetText(
//        FText::FromString(
//            FString::Printf(TEXT("나 : %d점"), LocalPS->GetMyScore())
//        )
//    );
//
//    EnemyScoreText->SetText(
//        FText::FromString(
//            FString::Printf(TEXT("상대방 : %d점"), OtherPS->GetMyScore())
//        )
//    );
//}