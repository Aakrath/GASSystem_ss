#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"          // FTableRowBase için
#include "Engine/Texture2D.h"          // Icon için
#include "ItemTypes.generated.h"

class UGameplayEffect;

// -------------------------------------------------------------
//                       Consumable Properties
// -------------------------------------------------------------
USTRUCT(BlueprintType)
struct FConsumableProps
{
	GENERATED_BODY()

	// Item kullanıldığında tetiklenecek GameplayEffect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Consumable")
	TSubclassOf<UGameplayEffect> ItemEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Consumable")
	float ItemEffectLevel = 1.f;
};


// -------------------------------------------------------------
//                   Master Item Definition
// -------------------------------------------------------------
USTRUCT(BlueprintType)
struct FMasterItemDefinition : public FTableRowBase
{
	GENERATED_BODY()

	// Item’ın sistem tagsı
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FGameplayTag ItemTag;

	// Runtime quantity (DataTable içinde kullanılmaz)
	UPROPERTY(BlueprintReadOnly, Category = "Item")
	int32 ItemQuantity = 1;

	// İsim
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	// İkon
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UTexture2D> Icon = nullptr;

	// Açıklama
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Description;

	// Potion / Consumable özellikleri
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Consumable")
	FConsumableProps ConsumableProps;
};