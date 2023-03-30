// Copyright Epic Games, Inc. All Rights Reserved.

#include "USDScriptingBPLibrary.h"
#include "USDScripting.h"
#include "USDScriptingWrappers.h"
#include "UnrealUSDWrapper.h"
#include "USDGeomMeshConversion.h"
#include "UsdWrappers/SdfPath.h"

FUsdScriptingStage UUSDScriptingBPLibrary::NewStage()
{
	return FUsdScriptingStage(UnrealUSDWrapper::NewStage());
}

bool UUSDScriptingBPLibrary::ExportFlattened(FUsdScriptingStage Stage, const FString& FilePath)
{
	return Stage.InternalStage.Export(*FilePath);
}

FUsdScriptingPrim UUSDScriptingBPLibrary::DefinePrim(
	FUsdScriptingStage Stage,
	const FString& PrimPath,
	const FString& PrimType
)
{
	return FUsdScriptingPrim(Stage.InternalStage.DefinePrim(UE::FSdfPath{*PrimPath}, *PrimType));
}

void UUSDScriptingBPLibrary::SetDefaultPrim(FUsdScriptingStage Stage, FUsdScriptingPrim Prim)
{
	Stage.InternalStage.SetDefaultPrim(Prim.InternalPrim);
}

bool UUSDScriptingBPLibrary::ConvertStaticMesh(FUsdScriptingPrim Prim, const UStaticMesh* StaticMesh)
{
	return UnrealToUsd::ConvertStaticMesh(StaticMesh, Prim.InternalPrim);
}
