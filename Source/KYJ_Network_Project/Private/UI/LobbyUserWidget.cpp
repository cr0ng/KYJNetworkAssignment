// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Framework/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULobbyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CreateButton)
	{
		CreateButton->OnClicked.AddDynamic(this, &ULobbyUserWidget::OnCreateButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ULobbyUserWidget::OnJoinButtonClicked);
	}
}

void ULobbyUserWidget::OnCreateButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("서버 생성 버튼 클릭"));
	UMainGameInstance* GI = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->CreateServer();
	}
}

void ULobbyUserWidget::OnJoinButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("서버 참여 버튼 클릭"));
	UMainGameInstance* GI = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		FString IPaddress = GI->GetIPAddress();
		if (ServerIPTextBox)
		{
			FString InputIP = ServerIPTextBox->GetText().ToString();
			if (InputIP.IsEmpty())
			{
				IPaddress = InputIP;
			}
		}
		GI->JoinServer(IPaddress);
	}
}