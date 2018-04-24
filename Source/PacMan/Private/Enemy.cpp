// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/Material.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemy::AEnemy()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(
        TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder'"));
    if (CylinderObj.Succeeded())
    {
        Body->SetStaticMesh(CylinderObj.Object);
    }

    Body->SetRelativeScale3D(FVector(0.7f, 0.7f, 1));
    Body->SetRelativeLocation(FVector(0, 0, -50));
    Body->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

    GetCapsuleComponent()->SetCapsuleRadius(40.0f, false);
    GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

    static ConstructorHelpers::FObjectFinder<UMaterial> VulnerableMatFinder(
        TEXT("Material'/Game/Materials/M_Vulnerable_Gray.M_Vulnerable_Gray''"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    DefaultMaterial = Body->GetMaterial(0);
    SetVulnerable();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::SetVulnerable()
{
    GetWorldTimerManager().SetTimer(VulnerableTimer, this, &AEnemy::SetInvulnerable, 10);
    if (bIsVulnerable)
        return;
    bIsVulnerable = true;
    Body->SetMaterial(0, VulnerableMaterial);
    GetCharacterMovement()->MaxWalkSpeed = 50;
}

void AEnemy::SetInvulnerable()
{
    GetWorldTimerManager().ClearTimer(VulnerableTimer);
    if (!bIsVulnerable)
        return;
    bIsVulnerable = false;
    Body->SetMaterial(0, DefaultMaterial);
    GetCharacterMovement()->MaxWalkSpeed = 150;
}