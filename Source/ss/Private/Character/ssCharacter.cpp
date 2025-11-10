// Copyright SS Mechanics


#include "Character/ssCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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

