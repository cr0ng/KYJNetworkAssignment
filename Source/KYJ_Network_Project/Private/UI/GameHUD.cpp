// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"
#include "Blueprint/UserWidget.h"

void AGameHUD::BeginPlay()
{
	if (GameHudWidgetClass)
	{
		GameHudWidget = CreateWidget<UUserWidget>(GetWorld(), GameHudWidgetClass);
		if (GameHudWidget.IsValid())
		{
			GameHudWidget->AddToViewport();
		}
	}
}
