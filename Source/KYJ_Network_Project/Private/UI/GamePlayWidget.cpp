// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GamePlayWidget.h"
#include "Framework/TestGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ResultText->SetVisibility(ESlateVisibility::Hidden);
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
	if (CachedGameState.IsValid() && CachedGameState->IsGameOver())
	{
		ResultText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		ResultText->SetVisibility(ESlateVisibility::Hidden);
	}
}
