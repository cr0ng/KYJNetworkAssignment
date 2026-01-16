// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KYJ_NETWORK_PROJECT_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMainGameInstance();

	virtual void Init() override;

	void CreateServer();
	void JoinServer(FString IPAddress);
	void DisconnectServer();

	inline const FString& GetIPAddress() const { return ServerIP; }

private:
	UFUNCTION()
	void HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	UFUNCTION()
	void HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString);

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Server")
	FString ServerIP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Server")
	TSoftObjectPtr<UWorld> LobbyLevelAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Server")
	TSoftObjectPtr<UWorld> GameLevelAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Server")
	int32 MaxPlayers = 2;
};
