// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SpawnPoint.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority() && SpawnActors)
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnPoint::SpawnActor, SpawnInterval, true);
	}
}

void ASpawnPoint::SpawnActor()
{
    if (!HasAuthority() || !SpawnActors)
        return;

    FVector BoxExtent = SpawnBox->GetScaledBoxExtent();
    FVector BoxOrigin = SpawnBox->GetComponentLocation();

    FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
        BoxOrigin,
        BoxExtent
    );

    //GEngine->AddOnScreenDebugMessage( -1,2.f,FColor::Green, TEXT("스폰 액터 생성됨") );

    GetWorld()->SpawnActor<AActor>(
        SpawnActors,
        SpawnLocation,
        FRotator::ZeroRotator
    );

}
