// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;

UCLASS()
class RECREATIONS_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlashCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
    virtual void BeginPlay() override;
    void MoveFoward(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void MoveRight(float Value);

public:	
    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComp;
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;
};
