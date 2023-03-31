// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsdWrappers/SdfLayer.h"
#include "UsdWrappers/UsdPrim.h"
#include "UsdWrappers/UsdStage.h"
#include "USDScriptingWrappers.generated.h"

UENUM(BlueprintType)
enum class EUsdScriptingKind : uint8
{
	None,
	Model,
	Component,
	Group,
	Assembly,
	Subcomponent
};

USTRUCT(BlueprintType)
struct USDSCRIPTING_API FUsdScriptingStage
{
	GENERATED_BODY()

	UE::FUsdStage InternalStage;

	FUsdScriptingStage();
	explicit FUsdScriptingStage(UE::FUsdStage InStage);
};

USTRUCT(BlueprintType)
struct USDSCRIPTING_API FUsdScriptingLayer
{
	GENERATED_BODY()

	UE::FSdfLayer InternalLayer;

	FUsdScriptingLayer();
	explicit FUsdScriptingLayer(UE::FSdfLayer InLayer);
};

USTRUCT(BlueprintType)
struct USDSCRIPTING_API FUsdScriptingPrim
{
	GENERATED_BODY()

	UE::FUsdPrim InternalPrim;

	FUsdScriptingPrim();
	explicit FUsdScriptingPrim(UE::FUsdPrim InPrim);
};
