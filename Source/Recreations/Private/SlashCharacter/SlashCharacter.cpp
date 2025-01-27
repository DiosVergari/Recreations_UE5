// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashCharacter/SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComp->SetupAttachment(GetRootComponent());

    ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    ViewCamera->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(FName("MoveFoward"), this, &ASlashCharacter::MoveFoward);
    PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASlashCharacter::MoveRight);
    PlayerInputComponent->BindAxis(FName("MouseX"), this, &ASlashCharacter::Turn);
    PlayerInputComponent->BindAxis(FName("MouseY"), this, &ASlashCharacter::LookUp);
}

void ASlashCharacter::MoveFoward(float Value)
{
    if(Controller == nullptr && Value == 0.0f)
        return;

    const FRotator controllerRot = GetControlRotation();
    const FRotator YawRotation(.0f, controllerRot.Yaw, .0f);

    const FVector dir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(dir, Value);
}

void ASlashCharacter::Turn(float Value)
{
    if(Controller == nullptr && Value == 0.0f)
        return;

    AddControllerYawInput(Value);
}

void ASlashCharacter::LookUp(float Value)
{
    if(Controller == nullptr && Value == 0.0f)
        return;

    AddControllerPitchInput(Value);
}

void ASlashCharacter::MoveRight(float Value)
{
    if(Controller == nullptr && Value == 0.0f)
        return;

    AddMovementInput(GetActorRightVector(), Value);
}