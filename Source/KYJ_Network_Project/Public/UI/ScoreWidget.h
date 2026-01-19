// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class KYJ_NETWORK_PROJECT_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateScore(class ATestPlayerState* LocalPS, class ATestPlayerState* OtherPS);


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MyScoreText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> EnemyScoreText = nullptr;
};
