// Copyright SS Mechanics


#include "Player/ssPlayerState.h"

#include "AbilitySystem/ssAbilitySystemComponent.h"
#include "AbilitySystem/ssAttributeSet.h"

AssPlayerState::AssPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UssAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UssAttributeSet>("AttributeSet");
	
	SetNetUpdateFrequency(100.f);

}

UAbilitySystemComponent* AssPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
