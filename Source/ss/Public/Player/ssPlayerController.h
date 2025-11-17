// Copyright SS Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "Inventory/ssInventoryComponent.h"
#include "ssPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;



UCLASS()
class SS_API AssPlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AssPlayerController();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void PlayerTick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"), Replicated)
	TObjectPtr<UssInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> ssContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InteractAction;

	void Move(const struct FInputActionValue& InputActionValue);
	void Interact(const FInputActionValue& InputActionValue);

	void CursorTrace();
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
};
