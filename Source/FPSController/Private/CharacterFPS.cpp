// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFPS.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACharacterFPS::ACharacterFPS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Player Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetMesh(), FName("head"));
}

// Called when the game starts or when spawned
void ACharacterFPS::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ACharacterFPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

