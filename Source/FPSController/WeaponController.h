#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponController.generated.h"

USTRUCT(BlueprintType)
struct AnimationProperties {

	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAnimSequence* AnimSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform OffsetTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AimDistance = 16.0f;
};

UCLASS(ABSTRACT)
class FPSCONTROLLER_API AWeaponController : public AActor {

	GENERATED_BODY()

public:
	// Sets default values for this empty's properties
	AWeaponController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "State")
		class ACharacterFPS* MyOwner;

	// Animation Specific Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configurations")
		AnimationProperties AnimProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configurations")
		FTransform OffsetTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USkeletalMeshComponent* SkeleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USceneComponent* Root;
};
