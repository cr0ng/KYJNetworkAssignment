// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePlayWidget.generated.h"

class UTextBlock;
class UScoreWidget;
/**
 * 
 */
UCLASS()
class KYJ_NETWORK_PROJECT_API UGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateScore(int32 NewScore);
	void UpdateScoreHUD();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateTimeDisplay();

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateGameOverDisplay();

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void OnScoreChanged(int32 MyScore, int32 OtherScore);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainingTimeText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScoreWidget> MyScoreText;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScoreWidget> EnemyScoreText;
	

private:
	TWeakObjectPtr<class ATestGameStateBase> CachedGameState = nullptr;
};
