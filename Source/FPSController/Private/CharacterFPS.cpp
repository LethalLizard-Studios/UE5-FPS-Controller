// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFPS.h"
#include "Camera/CameraComponent.h"
#include <Net/UnrealNetwork.h>

// Sets default values
ACharacterFPS::ACharacterFPS() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Player Camera
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));

	Cam -> bUsePawnControlRotation = true;
	Cam -> SetupAttachment(GetMesh(), FName("head"));
}

// Called when the game starts or when spawned
void ACharacterFPS::BeginPlay() {

	Super::BeginPlay();
	
	//If is your Player on network change weapons
	if (HasAuthority()) {
		for (const TSubclassOf<AWeaponController>& WeaponController : SpawnWeapon) {
			if (!WeaponController) continue;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			AWeaponController* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponController>(WeaponController, SpawnParams);
			const int32 Index = HeldWeapons.Add(SpawnedWeapon);

			if (SelectedIndex == Index) {
				SelectedWeapon = SpawnedWeapon;
				OnRep_SelectedWeapon(nullptr);
			}
		}
	}
}

void ACharacterFPS::OnRep_SelectedWeapon(const AWeaponController* PrevWeapon) {

	if (SelectedWeapon) {
		if (!SelectedWeapon->MyOwner) {
			const FTransform& OffsetTransform = SelectedWeapon->PlacementTransform * GetMesh()->GetSocketTransform(FName("Weapon_R"));

			SelectedWeapon->SetActorTransform(GetMesh()->GetSocketTransform(FName("Weapon_R")), false, nullptr, ETeleportType::TeleportPhysics);
			SelectedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("Weapon_R"));
			SelectedWeapon->Mesh->SetVisibility(true);
			SelectedWeapon->MyOwner = this;
		}
	}

	if (PrevWeapon) {

	}
}

void ACharacterFPS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ACharacterFPS, SelectedWeapon, COND_None);
	DOREPLIFETIME_CONDITION(ACharacterFPS, HeldWeapons, COND_None);
}

// Called to bind functionality to input
void ACharacterFPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Binding the Player input controls
	PlayerInputComponent->BindAxis(FName("LookY"), this, &ACharacterFPS::LookY);
	PlayerInputComponent->BindAxis(FName("LookX"), this, &ACharacterFPS::LookX);

	PlayerInputComponent->BindAxis(FName("WalkForward"), this, &ACharacterFPS::WalkForward);
	PlayerInputComponent->BindAxis(FName("WalkSide"), this, &ACharacterFPS::WalkSide);
}

void ACharacterFPS::LookY(const float Value) {
	AddControllerPitchInput(Value);
}

void ACharacterFPS::LookX(const float Value) {
	AddControllerYawInput(Value);
}

void ACharacterFPS::WalkForward(const float Value) {
	// Note: Figure out how to do both in one by having a UnitAxis variable
	const FVector& Dir = FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X);
	AddMovementInput(Dir, Value);
}

void ACharacterFPS::WalkSide(const float Value) {
	const FVector& Dir = FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y);
	AddMovementInput(Dir, Value);
}

