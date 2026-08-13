// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NBPawn.h"

#include "CH6_NumberBaseBall.h"

// Sets default values
ANBPawn::ANBPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANBPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = NBFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("NBPawn::BeginPlay() %s [%s]"),*NBFunctionLibrary::GetNetModeString(this),*NetRoleString);
	NBFunctionLibrary::MyPrintString(this,CombinedString,10.f);
}

void ANBPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	FString NetRoleString = NBFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("NBPawn::PossessedBy() %s [%s]"),*NBFunctionLibrary::GetNetModeString(this),*NetRoleString);
	NBFunctionLibrary::MyPrintString(this,CombinedString,10.f);

}

