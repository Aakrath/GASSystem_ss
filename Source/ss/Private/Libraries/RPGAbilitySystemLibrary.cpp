#include "Libraries/RPGAbilitySystemLibrary.h"
#include "Inventory/ItemTypes.h"
#include "Inventory/ItemTypesToTables.h"
#include "Engine/DataTable.h"



// -----------------------------------------------------
//     ITEM TAG → DATA TABLE ROW (Stable Copy Version)
// -----------------------------------------------------
bool URPGAbilitySystemLibrary::GetItemDefinitionByTag(
	const FGameplayTag& ItemTag,
	const UItemTypesToTables* TablesAsset,
	FMasterItemDefinition& OutDefinition
)
{
	if (!TablesAsset)
		return false;

	for (const auto& Pair : TablesAsset->TagsToTables)
	{
		const FGameplayTag& KeyTag = Pair.Key;
		UDataTable* Table = Pair.Value;

		if (!Table)
			continue;

		if (ItemTag.MatchesTag(KeyTag))
		{
			const FMasterItemDefinition* Row =
				GetDataTableRowByTag<FMasterItemDefinition>(Table, ItemTag);

			if (Row)
			{
				// ---- Manual Copy (Assignment forbidden workaround) ----
				OutDefinition.ItemTag           = Row->ItemTag;
				OutDefinition.ItemQuantity      = Row->ItemQuantity;
				OutDefinition.ItemName          = Row->ItemName;
				OutDefinition.Icon              = Row->Icon;
				OutDefinition.Description       = Row->Description;
				OutDefinition.ConsumableProps   = Row->ConsumableProps;
				// -------------------------------------------------------

				return true;
			}
		}
	}

	return false;
}