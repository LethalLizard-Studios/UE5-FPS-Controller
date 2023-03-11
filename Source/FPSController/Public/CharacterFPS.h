// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterFPS.generated.h"

UCLASS()
class FPSCONTROLLER_API ACharacterFPS : public ACharacter {

	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterFPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")

		class UCameraComponent* Cam;

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Replicated, Category = "State")
		TArray<class AWeaponController*> HeldWeapons;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, ReplicatedUsing = OnRep_SelectedWeapon, Category = "State")
		class AWeaponController* SelectedWeapon;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "State")
		int32 SelectedIndex = 0;

protected:
	UFUNCTION()
		virtual void OnRep_SelectedWeapon(const class AWeaponController* PrevWeapon);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Configurations")
		TArray<TSubclassOf<class AWeaponController>> SpawnWeapon;

protected:
	// Used to get (x,y) values of look rotation
	void LookY(const float Value);
	void LookX(const float Value);

	// Moves the player either side-to-side or forward/back
	void WalkForward(const float Value);
	void WalkSide(const float Value);
};

