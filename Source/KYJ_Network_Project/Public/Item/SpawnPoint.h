// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class KYJ_NETWORK_PROJECT_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Sapwn")
	TSubclassOf<AActor> SpawnActors;

	UPROPERTY(EditAnywhere, Category = "Sapwn")
	float SpawnInterval = 3.0f;

	FTimerHandle SpawnTimerHandle;

	void SpawnActor();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SpawnBox;
};
