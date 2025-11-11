// Copyright SS Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Character/ssCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "ssEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SS_API AssEnemy : public AssCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	
	AssEnemy();

		/** Enemy Interface*/
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
		/** Enemy Interface*/

protected:
	virtual void BeginPlay() override;

	
};
