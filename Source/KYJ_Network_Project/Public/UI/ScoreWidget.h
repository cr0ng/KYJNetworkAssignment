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
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	//void UpdateScore(class ATestPlayerState* LocalPS, class ATestPlayerState* OtherPS);
	void UpdateScore(int32 NewScore);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText = nullptr;
};
