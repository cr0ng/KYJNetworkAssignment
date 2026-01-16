// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "Blueprint/UserWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MainHudWidgetClass)
	{
		MainHudWidget = CreateWidget<UUserWidget>(GetWorld(), MainHudWidgetClass);
		if (MainHudWidget.IsValid())
		{
			MainHudWidget->AddToViewport();
		}
	}
}
