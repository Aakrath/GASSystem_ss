// Copyright SS Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ssCharacterBase.generated.h"

UCLASS(Abstract)
class SS_API AssCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AssCharacterBase();

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Combat") //Burada skeletalmesh için tanımlama yapılıyor//
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
