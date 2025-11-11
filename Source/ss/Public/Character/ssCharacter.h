// Copyright SS Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Character/ssCharacterBase.h"
#include "ssCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SS_API AssCharacter : public AssCharacterBase
{
	GENERATED_BODY()
public:
	AssCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	void InitAbiliyActorInfo();
};
