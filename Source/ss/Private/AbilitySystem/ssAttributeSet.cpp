// Copyright SS Mechanics


#include "AbilitySystem/ssAttributeSet.h"

#include "Net/UnrealNetwork.h"

UssAttributeSet::UssAttributeSet()
{
		InitHealth(100.f);
		InitMaxHealth(100.f);
		InitMana(50.f);
		InitMaxMana(50.f);
}

void UssAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UssAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UssAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UssAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UssAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	
	
		
}

void UssAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UssAttributeSet, Health, OldHealth);
}

void UssAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UssAttributeSet, MaxHealth, OldMaxHealth);
}

void UssAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UssAttributeSet, Mana, OldMana);
}

void UssAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UssAttributeSet, MaxMana, OldMaxMana);
}
