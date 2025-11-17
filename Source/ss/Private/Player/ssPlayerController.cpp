// Copyright SS Mechanics

#include "Player/ssPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interaction/EnemyInterface.h"
#include "Net/UnrealNetwork.h"

// -----------------------------------------------------
//                Constructor
// -----------------------------------------------------
AssPlayerController::AssPlayerController()
{
	bReplicates = true;

	InventoryComponent = CreateDefaultSubobject<UssInventoryComponent>(TEXT("InventoryComponent"));
	InventoryComponent->SetIsReplicated(true);
}

// -----------------------------------------------------
//        Ability System Access
// -----------------------------------------------------
UAbilitySystemComponent* AssPlayerController::GetAbilitySystemComponent() const
{
	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
}

void AssPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AssPlayerController, InventoryComponent);
}

// -----------------------------------------------------
//                Tick / Cursor Trace
// -----------------------------------------------------
void AssPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AssPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!Hit.bBlockingHit) return;

	AActor* HitActor = Hit.GetActor();
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

	if (!LastActor)
	{
		if (ThisActor) ThisActor->HighLightActor();
	}
	else
	{
		if (!ThisActor)
		{
			LastActor->UnHighLightActor();
		}
		else if (LastActor != ThisActor)
		{
			LastActor->UnHighLightActor();
			ThisActor->HighLightActor();
		}
	}
}

// -----------------------------------------------------
//                Begin Play
// -----------------------------------------------------
void AssPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(ssContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(ssContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Mode.SetHideCursorDuringCapture(false);
	SetInputMode(Mode);
}

// -----------------------------------------------------
//                Input Setup
// -----------------------------------------------------
void AssPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Movement
	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AssPlayerController::Move);

	// Interact / Use Item
	if (InteractAction)
	{
		EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &AssPlayerController::Interact);
	}
}

// -----------------------------------------------------
//                Input Functions
// -----------------------------------------------------
void AssPlayerController::Interact(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Interact Triggered"));

	if (!InventoryComponent) return;

	// Deneme için sabit bir Tag kullanıyoruz (BP'de değiştirilebilir)
	FGameplayTag ItemToUse = FGameplayTag::RequestGameplayTag(FName("Item.Potion.Health"));

	InventoryComponent->UseItem(ItemToUse, 1);
}

void AssPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	const FRotator Rot = GetControlRotation();
	const FRotator YawRot(0.f, Rot.Yaw, 0.f);

	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector Right   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	if (APawn* P = GetPawn<APawn>())
	{
		P->AddMovementInput(Forward, Input.Y);
		P->AddMovementInput(Right, Input.X);
	}
}