// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/NNPlayerCharacter.h"
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

/**
 * Constructor for ANNPlayerCharacter.TimerHan
 * Initializes the CameraBoom and Camera components and sets their properties.
 */
ANNPlayerCharacter::ANNPlayerCharacter()
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetMesh());

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);

    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->TargetArmLength = 300.f;
}

/**
 * Called when the game starts or when spawned.
 */
void ANNPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (_abilitySet != NULL) {
        
        _ability_1 = NewObject<UNNAbility>(this, _abilitySet->_ability_1);
        _ability_1->Init(this);

        _ability_2 = NewObject<UNNAbility>(this, _abilitySet->_ability_2);
        _ability_2->Init(this);

        _ability_3 = NewObject<UNNAbility>(this, _abilitySet->_ability_3);
        _ability_3->Init(this);
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("the ability set is null"));
}

/**
 * Called every frame.
 * @param DeltaTime - The time elapsed since the last frame.
 */
void ANNPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /*float mouseX;
    float mouseY;
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld()
    UE_LOG(LogTemp, Warning, TEXT("Mouse Location: %f, %f"), mouseX, mouseY);*/

    FHitResult Hit;
    bool bHitSuccessful = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

    FVector CachedDestination;

    if (bHitSuccessful)
    {
        CachedDestination = Hit.Location;
    }

    //UE_LOG(LogTemp, Warning, TEXT("Mouse Location: %f, %f"), CachedDestination.X, CachedDestination.Y);

    FVector worldDir = (CachedDestination - GetActorLocation()).GetSafeNormal();
    FVector alteredDir = FVector(worldDir.X, worldDir.Y, 0);
    alteredDir = alteredDir.RotateAngleAxis(-90.0f, FVector(0, 0, 1));

    
    GetMesh()->SetWorldRotation(FRotationMatrix::MakeFromX(alteredDir).Rotator());
}

/**
 * Called to bind functionality to input.
 * @param PlayerInputComponent - The input component to bind actions to.
 */
void ANNPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        Input->BindAction(ForwardAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::MoveForward);
        Input->BindAction(RightAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::MoveRight);
        Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HandlePlayerLook);
        Input->BindAction(DashAction, ETriggerEvent::Started, this, &ANNPlayerCharacter::HandlePlayerDash);

        Input->BindAction(Ability1Action, ETriggerEvent::Started, this, &ANNPlayerCharacter::StartPlayerAbility1);
        Input->BindAction(Ability1Action, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HoldPlayerAbility1);
        Input->BindAction(Ability1Action, ETriggerEvent::Completed, this, &ANNPlayerCharacter::EndPlayerAbility1);

        Input->BindAction(Ability2Action, ETriggerEvent::Started, this, &ANNPlayerCharacter::StartPlayerAbility2);
        Input->BindAction(Ability2Action, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HoldPlayerAbility2);
        Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &ANNPlayerCharacter::EndPlayerAbility2);

        Input->BindAction(Ability3Action, ETriggerEvent::Started, this, &ANNPlayerCharacter::StartPlayerAbility3);
        Input->BindAction(Ability3Action, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HoldPlayerAbility3);
        Input->BindAction(Ability3Action, ETriggerEvent::Completed, this, &ANNPlayerCharacter::EndPlayerAbility3);
    }
}

/**
 * Handles player movement input.
 * @param InputValue - The input value for movement.
 */
void ANNPlayerCharacter::HandlePlayerInputMove(const FInputActionValue& InputValue)
{
    FVector2D Movement = InputValue.Get<FVector2D>();
    AddMovementInput(FVector(Movement.Y, Movement.X, 0));
}

/**
 * Moves the player character forward.
 * @param InputValue - The input value for forward movement.
 */
void ANNPlayerCharacter::MoveForward(const FInputActionValue& InputValue)
{
    FVector2D AxisVector = InputValue.Get<FVector2D>();
    float AxisValue = AxisVector.Y;

    if ((Controller != nullptr) && (AxisValue != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, AxisValue);
    }
}

/**
 * Moves the player character to the right.
 * @param InputValue - The input value for right movement.
 */
void ANNPlayerCharacter::MoveRight(const FInputActionValue& InputValue)
{
    FVector2D AxisVector = InputValue.Get<FVector2D>();
    float AxisValue = AxisVector.Y;

    if ((Controller != nullptr) && (AxisValue != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, AxisValue);
    }
}

/**
 * Handles the player dash action.
 * Temporarily increases the character's max walk speed.
 */
void ANNPlayerCharacter::HandlePlayerDash()
{
    GetCharacterMovement()->MaxWalkSpeed = 2000.f;
    GetWorldTimerManager().SetTimer(DashTimerHandle, this, &ANNPlayerCharacter::ResetDash, .25f, false);
}

/**
 * Handles player look input.
 * @param InputValue - The input value for looking around.
 */
void ANNPlayerCharacter::HandlePlayerLook(const FInputActionValue& InputValue)
{
    FVector2D Movement = InputValue.Get<FVector2D>();
    AddControllerYawInput(Movement.X);
}

/**
 * Handles the first player ability.
 * @param InputValue - The input value for the ability.
 */
void ANNPlayerCharacter::StartPlayerAbility1(const FInputActionValue& InputValue)
{
    _ability_1->Trigger(KeyState::Start);
}

void ANNPlayerCharacter::HoldPlayerAbility1(const FInputActionValue& InputValue)
{
    _ability_1->Trigger(KeyState::Hold);
}

void ANNPlayerCharacter::EndPlayerAbility1(const FInputActionValue& InputValue)
{
    _ability_1->Trigger(KeyState::End);
}

/**
 * Handles the second player ability.
 * @param InputValue - The input value for the ability.
 */
void ANNPlayerCharacter::StartPlayerAbility2(const FInputActionValue& InputValue)
{
    _ability_2->Trigger(KeyState::Start);
}

void ANNPlayerCharacter::HoldPlayerAbility2(const FInputActionValue& InputValue)
{
    _ability_2->Trigger(KeyState::Hold);
}

void ANNPlayerCharacter::EndPlayerAbility2(const FInputActionValue& InputValue)
{
    _ability_2->Trigger(KeyState::End);
}

/**
 * Handles the third player ability.
 * @param InputValue - The input value for the ability.
 */
void ANNPlayerCharacter::StartPlayerAbility3(const FInputActionValue& InputValue)
{
    _ability_3->Trigger(KeyState::Start);
}

void ANNPlayerCharacter::HoldPlayerAbility3(const FInputActionValue& InputValue)
{
    _ability_3->Trigger(KeyState::Hold);
}

void ANNPlayerCharacter::EndPlayerAbility3(const FInputActionValue& InputValue)
{
    _ability_3->Trigger(KeyState::End);
}


void ANNPlayerCharacter::ResetDash()
{
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
}