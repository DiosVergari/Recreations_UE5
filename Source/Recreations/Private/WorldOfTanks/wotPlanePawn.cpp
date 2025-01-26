#include "WorldOfTanks/wotPlanePawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"

AwotPlanePawn::AwotPlanePawn()
{
    PrimaryActorTick.bCanEverTick = true;
    RotationLerpProgress = 1.f; // Start fully completed (no active lerp)

    // Initialize components
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeleton Component"));
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

    SetRootComponent(CapsuleComp);
    SkeletonMesh->SetupAttachment(CapsuleComp);
    SpringArm->SetupAttachment(SkeletonMesh);
    CameraComp->SetupAttachment(SpringArm);

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AwotPlanePawn::BeginPlay()
{
    Super::BeginPlay();
    SetupInformation();
}

void AwotPlanePawn::SetupInformation()
{
    RowPlaneData = PlaneData->FindRow<FPlaneData>(RowName, "");
    EnginePercentage = EnginePercentageStart;
    SkeletonMesh->SetSkeletalMeshAsset(RowPlaneData->PlaneMesh);
    RotationCurve = Cast<UCurveFloat>(RowPlaneData->AnimationCurvePath.TryLoad());
}

void AwotPlanePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    LerpRotator(DeltaTime);
    PlaneAcceleration(DeltaTime);
}

void AwotPlanePawn::LerpRotator(float DeltaTime)
{
    if(RotationLerpProgress >= 1.f || RowPlaneData == nullptr)
        return;

    RotationLerpProgress += RotationCurve->GetFloatValue(EnginePercentage) * DeltaTime;
    RotationLerpProgress = FMath::Clamp(RotationLerpProgress, 0.f, 1.f);

    if(Controller)
    {
        FRotator CurrentRotation = CapsuleComp->GetComponentRotation();
        FRotator TargetRotation = Controller->GetControlRotation();
        FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, RotationLerpProgress);
        CapsuleComp->SetWorldRotation(NewRotation);
    }
}

void AwotPlanePawn::PlaneAcceleration(float DeltaTime)
{
    float CurrentSpeed = RowPlaneData->MinSpeed + (RowPlaneData->MaxSpeed - RowPlaneData->MinSpeed) * (EnginePercentage * 0.01f);

    if(CapsuleComp)
    {
        FVector Movement = CapsuleComp->GetForwardVector() * CurrentSpeed * DeltaTime;
        FVector NewPosition = CapsuleComp->GetComponentLocation() + Movement;
        CapsuleComp->SetWorldLocation(NewPosition);
    }
}

void AwotPlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(FName("MouseX"), this, &AwotPlanePawn::MouseX);
    PlayerInputComponent->BindAxis(FName("MouseY"), this, &AwotPlanePawn::MouseY);
    PlayerInputComponent->BindAxis(FName("EnginePercentage"), this, &AwotPlanePawn::EnginePercentageChange);
}

void AwotPlanePawn::MouseX(float Value)
{
    if(Value != 0.f && Controller)
    {
        AddControllerYawInput(Value);
        RotationLerpProgress = 0.f; // Reset lerp progress
    }
}

void AwotPlanePawn::MouseY(float Value)
{
    if(Value != 0.f && Controller)
    {
        AddControllerPitchInput(Value);
        RotationLerpProgress = 0.f; // Reset lerp progress
    }
}

void AwotPlanePawn::EnginePercentageChange(float Value)
{
    if(Value != 0.f && Controller)
    {
        EnginePercentage = FMath::Clamp(EnginePercentage + (int)Value, 0, 100);
    }
}