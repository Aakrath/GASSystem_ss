// Copyright SS Mechanics


#include "Character/ssCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ssPlayerState.h"

AssCharacter::AssCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	
	GetCharacterMovement()->bConstrainToPlane = true;
	/// topdown game için karakteri planeeSabitleme z eksenini yokediyor sonradan değiştirmem gerekebilir///
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AssCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor info For the server
	InitAbiliyActorInfo();
}

void AssCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for client
	InitAbiliyActorInfo();
}

void AssCharacter::InitAbiliyActorInfo()
{
	AssPlayerState* ssPlayerState = GetPlayerState<AssPlayerState>();
	check(ssPlayerState);
	ssPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ssPlayerState, this);
	AbilitySystemComponent = ssPlayerState->GetAbilitySystemComponent();
	AttributeSet = ssPlayerState->GetAttributeSet();
}

