// Copyright SS Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "RPGAbilitySystemLibrary.generated.h"

class UItemTypesToTables;
struct FMasterItemDefinition;

UCLASS()
class SS_API URPGAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Belirli bir item tag için tabloyu bul ve item definition döndür */
	UFUNCTION(BlueprintPure, Category="Items")
	static bool GetItemDefinitionByTag(
		const FGameplayTag& ItemTag,
		const UItemTypesToTables* TablesAsset,
		FMasterItemDefinition& OutDefinition
	);

	/** Template Row Getter */
	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
	{
		if (!DataTable)
			return nullptr;

		FString Context;
		return DataTable->FindRow<T>(Tag.GetTagName(), Context, true);
	}
};
