// Copyright SS Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "ItemTypesToTables.generated.h"

UCLASS()
class SS_API UItemTypesToTables : public UDataAsset
{
	GENERATED_BODY()

public:

	// Constructor declaration
	UItemTypesToTables();

	// Tag → DataTable eşlemesi
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Items")
	TMap<FGameplayTag, TObjectPtr<UDataTable>> TagsToTables;
};