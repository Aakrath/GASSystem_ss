#include "Inventory/ssInventoryComponent.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Libraries/RPGAbilitySystemLibrary.h"
#include "Inventory/ItemTypesToTables.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"

bool FPackagedInventory::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	int32 Count = ItemTags.Num();
	Ar << Count;

	if (Ar.IsLoading())
	{
		ItemTags.SetNum(Count);
		ItemQuantities.SetNum(Count);
	}

	for (int32 i = 0; i < Count; i++)
	{
		ItemTags[i].NetSerialize(Ar, Map, bOutSuccess);
		Ar << ItemQuantities[i];
	}

	bOutSuccess = true;
	return true;
}

UssInventoryComponent::UssInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UssInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UssInventoryComponent, CachedInventory);
}

void UssInventoryComponent::AddItem(const FGameplayTag& ItemTag, int32 NumItems)
{
	AActor* Owner = GetOwner();
	if (!IsValid(Owner)) return;

	if (!Owner->HasAuthority())
	{
		ServerAddItem(ItemTag, NumItems);
		return;
	}

	if (InventoryTagMap.Contains(ItemTag))
	{
		InventoryTagMap[ItemTag] += NumItems;
	}
	else
	{
		InventoryTagMap.Emplace(ItemTag, NumItems);
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 3.f, FColor::Yellow,
			FString::Printf(TEXT("Item Added: %s | Qty: %d"),
			*ItemTag.ToString(), NumItems));
	}

	PackageInventory(CachedInventory);
}

FMasterItemDefinition UssInventoryComponent::GetItemDefinitionByTag(const FGameplayTag& ItemTag) const
{
	checkf(InventoryDefinition, TEXT("No Inventory Definition Inside Component %s"), *GetNameSafe(this));

	for (const auto& Pair : InventoryDefinition->TagsToTables)
	{
		if (ItemTag.MatchesTag(Pair.Key))
		{
			return *URPGAbilitySystemLibrary::GetDataTableRowByTag<FMasterItemDefinition>(Pair.Value, ItemTag);
		}
	}

	return FMasterItemDefinition();
}

void UssInventoryComponent::PackageInventory(FPackagedInventory& OutInventory)
{
	OutInventory.ItemTags.Empty();
	OutInventory.ItemQuantities.Empty();

	for (const auto& Pair : InventoryTagMap)
	{
		if (Pair.Value > 0)
		{
			OutInventory.ItemTags.Add(Pair.Key);
			OutInventory.ItemQuantities.Add(Pair.Value);
		}
	}
}

void UssInventoryComponent::ReconstructInventoryMap(const FPackagedInventory& Inventory)
{
	InventoryTagMap.Empty();

	for (int32 i = 0; i < Inventory.ItemTags.Num(); ++i)
	{
		InventoryTagMap.Emplace(Inventory.ItemTags[i], Inventory.ItemQuantities[i]);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 5.f, FColor::Blue,
				FString::Printf(TEXT("Tag Added: %s // Quantity Added: %d"),
				*Inventory.ItemTags[i].ToString(),
				Inventory.ItemQuantities[i]));
		}
	}
}

void UssInventoryComponent::OnRep_CachedInventory()
{
	ReconstructInventoryMap(CachedInventory);
}

void UssInventoryComponent::UseItem(const FGameplayTag& ItemTag, int32 NumItems)
{
	AActor* Owner = GetOwner();
	if (!IsValid(Owner)) return;

	// Client → Server
	if (!Owner->HasAuthority())
	{
		ServerUseItem(ItemTag, NumItems);
		return;
	}

	// Stok kontrolü
	if (!InventoryTagMap.Contains(ItemTag) || InventoryTagMap[ItemTag] <= 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 2.f, FColor::Red,
				TEXT("UseItem: No item in inventory"));
		}
		return;
	}

	// Item tanımı
	const FMasterItemDefinition Item = GetItemDefinitionByTag(ItemTag);

	// ---- ASC'yi Owner'dan (Controller) al → o da Pawn'dan çekiyor ----
	UAbilitySystemComponent* ASC =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);

	if (!ASC)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 2.f, FColor::Red,
				TEXT("UseItem: Owner has no ASC (AbilitySystemComponent)"));
		}
		return;
	}

	// Effect tanımlı mı?
	if (IsValid(Item.ConsumableProps.ItemEffectClass))
	{
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle =
			ASC->MakeOutgoingSpec(
				Item.ConsumableProps.ItemEffectClass,
				Item.ConsumableProps.ItemEffectLevel,
				Context);

		if (SpecHandle.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}

		// Envanterden 1 düş
		InventoryTagMap[ItemTag]--;

		if (InventoryTagMap[ItemTag] <= 0)
		{
			InventoryTagMap.Remove(ItemTag);
		}

		PackageInventory(CachedInventory);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 5.f, FColor::Magenta,
				FString::Printf(TEXT("Server Used Item: %s"), *Item.ItemTag.ToString()));
		}
	}
}

void UssInventoryComponent::ServerUseItem_Implementation(const FGameplayTag& ItemTag, int32 NumItems)
{
	UseItem(ItemTag, NumItems);
}

void UssInventoryComponent::ServerAddItem_Implementation(const FGameplayTag& ItemTag, int32 NumItems)
{
	AddItem(ItemTag, NumItems);
}
