// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NBPlayerState.h"

#include "Net/UnrealNetwork.h"

ANBPlayerState::ANBPlayerState() : PlayerNameString(TEXT("None")),CurrentGeuessCount(0),MaxGuessCount(3)
{
	bReplicates = true;
}

void ANBPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass,PlayerNameString);
	DOREPLIFETIME(ThisClass,CurrentGeuessCount);
	DOREPLIFETIME(ThisClass,MaxGuessCount);
	
}

FString ANBPlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerNameString + TEXT("(") + FString::FromInt(CurrentGeuessCount) + TEXT("/") + FString::FromInt(MaxGuessCount) + TEXT(")");
	return PlayerInfoString;
}
