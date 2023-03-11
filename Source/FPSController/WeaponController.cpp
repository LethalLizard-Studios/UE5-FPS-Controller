#include "WeaponController.h"

// Sets default values
AWeaponController::AWeaponController() {

	// Set this empty to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetReplicates(true);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SkeleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeleMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeaponController::BeginPlay() {

	Super::BeginPlay();

	Mesh->SetVisibility(false);
}


