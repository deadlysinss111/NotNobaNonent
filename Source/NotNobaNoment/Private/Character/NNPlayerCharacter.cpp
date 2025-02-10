// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/NNPlayerCharacter.h"
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

/**
 * Constructor for ANNPlayerCharacter.
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
        _attack = NewObject<UNNAbility>(this, _abilitySet->_attack);
        _attack->Init(this);
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
        Input->BindAction(Ability1Action, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HandlePlayerAbility1);
        Input->BindAction(Ability2Action, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HandlePlayerAbility2);
        Input->BindAction(Ability3Action, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HandlePlayerAbility3);
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
void ANNPlayerCharacter::HandlePlayerAbility1(const FInputActionValue& InputValue)
{
    UE_LOG(LogTemp, Warning, TEXT("Ability 1"));
}

/**
 * Handles the second player ability.
 * @param InputValue - The input value for the ability.
 */
void ANNPlayerCharacter::HandlePlayerAbility2(const FInputActionValue& InputValue)
{
    UE_LOG(LogTemp, Warning, TEXT("Ability 2"));
}

/**
 * Handles the third player ability.
 * @param InputValue - The input value for the ability.
 */
void ANNPlayerCharacter::HandlePlayerAbility3(const FInputActionValue& InputValue)
{
    UE_LOG(LogTemp, Warning, TEXT("Ability 3"));
}

/**
 * Resets the character's max walk speed to its default value.
 */
void ANNPlayerCharacter::ResetDash()
{
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ANNPlayerCharacter::TriggerAttack() {
    _attack->Trigger();
}

void ANNPlayerCharacter::TriggerAbility_1() {
    _ability_1->Trigger();
}

void ANNPlayerCharacter::TriggerAbility_2() {
    _ability_2->Trigger();
}