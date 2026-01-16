// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUserWidget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class KYJ_NETWORK_PROJECT_API ULobbyUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnCreateButtonClicked();

	UFUNCTION()
	void OnJoinButtonClicked();

protected:
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UButton> CreateButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ServerIPTextBox = nullptr;


};
