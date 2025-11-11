// Copyright SS Mechanics


#include "Character/ssEnemy.h"

#include "AbilitySystem/ssAbilitySystemComponent.h"
#include "AbilitySystem/ssAttributeSet.h"
#include "ss/ss.h"

AssEnemy::AssEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UssAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UssAttributeSet>("AttributeSet");
}

void AssEnemy::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AssEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AssEnemy::BeginPlay()
{
	Super::BeginPlay();	
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
