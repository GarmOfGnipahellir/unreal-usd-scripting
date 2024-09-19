// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsdWrappers/SdfLayer.h"
#include "UsdWrappers/UsdPrim.h"
#include "UsdWrappers/UsdStage.h"
#include "USDScriptingWrappers.generated.h"

#define USD_SCRIPTING_WRAPPER(WrappedType, WrapperIdent) \
		WrappedType Internal; \
\
		WrapperIdent() : Internal(WrappedType()) {} \
		explicit WrapperIdent(WrappedType InInternal) : Internal(InInternal) {} \
\
		WrappedType & operator*() { return Internal; } \
		WrappedType * operator->() { return &Internal; }

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

	USD_SCRIPTING_WRAPPER(UE::FUsdStage, FUsdScriptingStage)
};

USTRUCT(BlueprintType)
struct USDSCRIPTING_API FUsdScriptingLayer
{
	GENERATED_BODY()

	USD_SCRIPTING_WRAPPER(UE::FSdfLayer, FUsdScriptingLayer)
};

USTRUCT(BlueprintType)
struct USDSCRIPTING_API FUsdScriptingPrim
{
	GENERATED_BODY()

	USD_SCRIPTING_WRAPPER(UE::FUsdPrim, FUsdScriptingPrim)
};
