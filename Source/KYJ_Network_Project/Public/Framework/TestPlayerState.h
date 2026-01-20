// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TestPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMyScoreChanged, int32);

/**
 * 
 */
UCLASS()
class KYJ_NETWORK_PROJECT_API ATestPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Point);

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetMyScore() const { return MyScore; }

	FOnMyScoreChanged OnMyScoreChanged;

	UPROPERTY(ReplicatedUsing = OnRep_MyScore, BlueprintReadOnly, Category = "Data")
	int32 MyScore = 0;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_MyScore();

protected:


	TWeakObjectPtr<class UGamePlayWidget> ScoreHud = nullptr;
};
