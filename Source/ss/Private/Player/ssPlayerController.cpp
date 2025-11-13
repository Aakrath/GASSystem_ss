// Copyright SS Mechanics


#include "Player/ssPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AssPlayerController::AssPlayerController()
{
	bReplicates = true;
}

void AssPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AssPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	AActor* HitActor = CursorHit.GetActor();

	LastActor = ThisActor;

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass()))
	{
		ThisActor.SetObject(HitActor);
		ThisActor.SetInterface(Cast<IEnemyInterface>(HitActor));
	}
	else
	{
		ThisActor.SetObject(nullptr);
		ThisActor.SetInterface(nullptr);
	}

	/**
	 * line trace from cursor. There are several scenarios
	 */
	if (!LastActor)
	{
		if (ThisActor)
		{
			// Case B
			ThisActor->HighLightActor();
		}
		// Case A - both are null, do nothing
	}
	else
	{
		if (!ThisActor)
		{
			// Case C
			LastActor->UnHighLightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
			// Case E - do nothing
		}
	}
}



void AssPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(ssContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(ssContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void AssPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AssPlayerController::Move);
}

void AssPlayerController::Move(const struct FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation= GetControlRotation();
	const FRotator YawRotation (0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

