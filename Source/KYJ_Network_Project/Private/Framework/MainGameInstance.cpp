// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"


UMainGameInstance::UMainGameInstance()
{
	ServerIP = "127.0.0.1";
}

void UMainGameInstance::Init()
{
	Super::Init();

	if (UEngine* Engine = GetEngine())
	{
		Engine->OnNetworkFailure().AddUObject(this, &UMainGameInstance::HandleNetworkFailure);
		Engine->OnTravelFailure().AddUObject(this, &UMainGameInstance::HandleTravelFailure);
	}
}

void UMainGameInstance::CreateServer()
{
	FString MapName;
	if (!GameLevelAsset.IsNull())
	{
		MapName = GameLevelAsset.GetLongPackageName();
	}
	else
	{
		MapName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		// World 없음
		return;
	}

	FString Options = FString::Printf(TEXT("listen?MaxPlayers=%d"), MaxPlayers);

	UGameplayStatics::OpenLevel(World, FName(*MapName), true, Options);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Cyan, TEXT("리슨 서버 시작"));
	}
}

void UMainGameInstance::JoinServer(FString IPAddress)
{
	if (IPAddress.IsEmpty())
	{
		IPAddress = ServerIP;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
	{
		return;
	}

	PC->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Cyan, TEXT("서버 접속 시작"));
	}
}

void UMainGameInstance::DisconnectServer()
{
	FString MapName;
	if (!GameLevelAsset.IsNull())
	{
		MapName = GameLevelAsset.GetLongPackageName();
	}
	else
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
	{
		return;
	}

	PC->ClientTravel(MapName, ETravelType::TRAVEL_Absolute);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Cyan, TEXT("서버 접속 해제"));
	}
}


void UMainGameInstance::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogNet, Error, TEXT("HandleNetworkFailure 실행"));
	UE_LOG(LogNet, Error, TEXT("오류 타입 : %d"), (int32)FailureType);
	UE_LOG(LogNet, Error, TEXT("오류 메세지 : %s"), *ErrorString);
}

void UMainGameInstance::HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogNet, Error, TEXT("HandleTravelFailure 실행"));
	UE_LOG(LogNet, Error, TEXT("오류 타입 : %d"), (int32)FailureType);
	UE_LOG(LogNet, Error, TEXT("오류 메세지 : %s"), *ErrorString);

	switch (FailureType)
	{
	case ETravelFailure::ServerTravelFailure:
		if (ErrorString.Contains(TEXT("Full")) || ErrorString.Contains(TEXT("full")))
		{
			UE_LOG(LogNet, Error, TEXT("서버가 가득 찼다"));
		}
		break;
	default:
		break;
	}
}
