// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UUserWidget;
class UScoreWidget;
/**
 * 
 */
UCLASS()
class KYJ_NETWORK_PROJECT_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	inline TWeakObjectPtr<UUserWidget> GetScoreWidget() const { return GameHudWidget; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameHudWidgetClass = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UUserWidget> GameHudWidget = nullptr;
	
};
