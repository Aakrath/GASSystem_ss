// Copyright SS Mechanics


#include "Character/ssCharacterBase.h"


AssCharacterBase::AssCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket")); //karakter meshinde buradaki soket adını kopyalıyoruz//
	
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AssCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AssCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

