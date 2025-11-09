// Copyright SS Mechanics


#include "ssCharacterBase.h"

// Sets default values
AssCharacterBase::AssCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AssCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AssCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AssCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

