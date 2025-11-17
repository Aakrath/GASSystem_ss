#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ItemTypes.h"
#include "ItemTypesToTables.h"
#include "ssInventoryComponent.generated.h"

USTRUCT()
struct FPackagedInventory
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FGameplayTag> ItemTags;

	UPROPERTY()
	TArray<int32> ItemQuantities;

	bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);
};

template<>
struct TStructOpsTypeTraits<FPackagedInventory> : public TStructOpsTypeTraitsBase2<FPackagedInventory>
{
	enum { WithNetSerializer = true };
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SS_API UssInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UssInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void AddItem(const FGameplayTag& ItemTag, int32 NumItems = 1);

	UFUNCTION(BlueprintCallable)
	void UseItem(const FGameplayTag& ItemTag, int32 NumItems = 1);

	UFUNCTION(BlueprintPure)
	FMasterItemDefinition GetItemDefinitionByTag(const FGameplayTag& ItemTag) const;

private:

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, int32> InventoryTagMap;

	UPROPERTY(ReplicatedUsing=OnRep_CachedInventory)
	FPackagedInventory CachedInventory;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UItemTypesToTables> InventoryDefinition;

	UFUNCTION()
	void OnRep_CachedInventory();

	UFUNCTION(Server, Reliable)
	void ServerAddItem(const FGameplayTag& ItemTag, int32 NumItems);

	UFUNCTION(Server, Reliable)
	void ServerUseItem(const FGameplayTag& ItemTag, int32 NumItems);

	void PackageInventory(FPackagedInventory& OutInventory);
	void ReconstructInventoryMap(const FPackagedInventory& Inventory);
};
