// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "wotPlanePawn.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;

USTRUCT(BlueprintType)
struct FPlaneData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USkeletalMesh* PlaneMesh;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FSoftObjectPath AnimationCurvePath;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int MaxSpeed;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int MinSpeed;
};

UCLASS()
class RECREATIONS_API AwotPlanePawn : public APawn
{
	GENERATED_BODY()

private:
    AwotPlanePawn();
    ~AwotPlanePawn();
	virtual void BeginPlay() override; 
    void SetupInformation();
	virtual void Tick(float DeltaTime) override;
    void LerpRotator(float DeltaTime);
    void PlaneAcceleration(float DeltaTime);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    FPlaneData* RowPlaneData;

    UCurveFloat* RotationCurve;
    float RotationLerpProgress;
    float EngineForce;
    UPROPERTY(VisibleAnywhere)
    int EnginePercentage;

protected:
    void MouseX(float Value);
    void MouseY(float Value);
    void EnginePercentageChange(float Value);

    UPROPERTY(EditAnywhere)
    UDataTable* PlaneData;
    UPROPERTY(EditAnywhere)
    FName RowName;

    UPROPERTY(EditAnywhere)
    UCapsuleComponent* CapsuleComp;
    UPROPERTY(EditAnywhere)
    USkeletalMeshComponent* SkeletonMesh;
    UPROPERTY(EditAnywhere)
    UCameraComponent* CameraComp;
    UPROPERTY(EditAnywhere)
    USpringArmComponent* SpringArm;
    UPROPERTY(EditAnywhere)
    float EnginePercentageStart;

public:	
};
