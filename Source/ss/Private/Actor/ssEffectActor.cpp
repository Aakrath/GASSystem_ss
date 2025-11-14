// Copyright SS Mechanics


#include "Actor/ssEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/ssAttributeSet.h"
#include "Components/SphereComponent.h"


AssEffectActor::AssEffectActor()
{
 
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	

}

void AssEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//Change this apply a game play effect.For now,using 
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor)) 
	{
		const UssAttributeSet* ssAttributeSet = Cast<UssAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UssAttributeSet::StaticClass()));
		
		UssAttributeSet* MutablessAttributeSet = const_cast<UssAttributeSet*>(ssAttributeSet);
		MutablessAttributeSet->SetHealth(ssAttributeSet->GetHealth() +25.f);
		MutablessAttributeSet->SetMana(ssAttributeSet->GetMana() -25.f);
		Destroy();
	}
}


void AssEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


void AssEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AssEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AssEffectActor::EndOverlap);
	
}




