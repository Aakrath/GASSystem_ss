// Copyright SS Mechanics

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SS_API IEnemyInterface
{
	GENERATED_BODY()

	// Bpinterfacein cpp versiyonu burada altta tanımlama yapılıyor mesaj ileticek kısım interface.
public:
	
	virtual void HighLightActor() = 0;
	virtual void UnHighLightActor() = 0;
};
