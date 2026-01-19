// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PointActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Framework/TestPlayerState.h"


// Sets default values
APointActor::APointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(100.0f);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetRelativeLocation(FVector::UpVector * 100.0f);
}

// Called when the game starts or when spawned
void APointActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		OnActorBeginOverlap.AddDynamic(this, &APointActor::OnOverlapEvent);
	}
}

void APointActor::OnOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("OnOverlapEvent 실행"));
	if (HasAuthority())
	{
	UE_LOG(LogTemp, Log, TEXT("HasAuthority 실행"));
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			UE_LOG(LogTemp, Log, TEXT("Character 실행"));
			ATestPlayerState* PS = Character->GetPlayerState<ATestPlayerState>();
			if (PS)
			{
				UE_LOG(LogTemp, Log, TEXT("PS 실행"));
				PS->AddScore(Point);
				Destroy();
			}
		}
	}
}

