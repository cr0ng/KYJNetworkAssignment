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
	if (HasAuthority())
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			ATestPlayerState* PS = Character->GetPlayerState<ATestPlayerState>();
			if (PS)
			{
				PS->AddScore(Point);
				Destroy();
			}
		}
	}
}

