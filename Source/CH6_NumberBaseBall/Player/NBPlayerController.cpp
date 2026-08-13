// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NBPlayerController.h"

#include "CH6_NumberBaseBall.h"
#include "NBPlayerState.h"
#include "Game/NBGameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "UI/NBChatInput.h"

ANBPlayerController::ANBPlayerController()
{
	bReplicates = true;
}

void ANBPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController()==false)
		return;
	
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	
	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UNBChatInput>(this,ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
			ChatInputWidgetInstance->AddToViewport();
	}
	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTEXTWidgetInstance = CreateWidget<UUserWidget>(this,NotificationTextWidgetClass);
		if (IsValid(NotificationTEXTWidgetInstance) == true)
		{
			NotificationTEXTWidgetInstance->AddToViewport();
		}
	}
}

void ANBPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass,NotificationText);
}

void ANBPlayerController::SetChatMessageString(const FString& InChatMessageString)
{	
	if (IsLocalController() ==true)
	{
			ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ANBPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	NBFunctionLibrary::MyPrintString(this,InChatMessageString,10.f);
}

void ANBPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ANBGameModeBase* NBGM = Cast<ANBGameModeBase>(GM);
		if (IsValid(NBGM) == true)
		{
			NBGM->PrintChatMessageString(this,InChatMessageString);
		}
	}
}

void ANBPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}
