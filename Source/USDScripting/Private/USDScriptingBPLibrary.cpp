// Copyright Epic Games, Inc. All Rights Reserved.

#include "USDScriptingBPLibrary.h"
#include "USDScripting.h"
#include "USDScriptingWrappers.h"
#include "UnrealUSDWrapper.h"
#include "USDConversionUtils.h"
#include "USDGeomMeshConversion.h"
#include "USDPrimConversion.h"
#include "UsdWrappers/SdfPath.h"

FUsdScriptingStage UUSDScriptingBPLibrary::NewStage()
{
	return FUsdScriptingStage(UnrealUSDWrapper::NewStage());
}

FUsdScriptingStage UUSDScriptingBPLibrary::StageOpenLayer(FUsdScriptingLayer Layer)
{
	return FUsdScriptingStage(
		UnrealUSDWrapper::OpenStage(Layer.InternalLayer, UE::FSdfLayer(), EUsdInitialLoadSet::LoadAll)
	);
}

FUsdScriptingLayer UUSDScriptingBPLibrary::GetRootLayer(FUsdScriptingStage Stage)
{
	return FUsdScriptingLayer(Stage.InternalStage.GetRootLayer());
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

FUsdScriptingLayer UUSDScriptingBPLibrary::LayerFindOrOpen(const FString& Identifier, bool& bSuccess)
{
	UE::FSdfLayer Layer = UE::FSdfLayer::FindOrOpen(*Identifier);
	bSuccess = (bool)Layer;
	return FUsdScriptingLayer(Layer);
}

FUsdScriptingLayer UUSDScriptingBPLibrary::LayerCreateNew(const FString& Identifier)
{
	return FUsdScriptingLayer(UE::FSdfLayer::CreateNew(*Identifier));
}

FString UUSDScriptingBPLibrary::GetLayerIdentifier(FUsdScriptingLayer Layer)
{
	return Layer.InternalLayer.GetIdentifier();
}

void UUSDScriptingBPLibrary::LayerClear(FUsdScriptingLayer Layer)
{
	Layer.InternalLayer.Clear();
}

bool UUSDScriptingBPLibrary::LayerSave(FUsdScriptingLayer Layer, bool bForce)
{
	return Layer.InternalLayer.Save(bForce);
}

bool UUSDScriptingBPLibrary::ConvertXformable(FUsdScriptingPrim Prim, const FTransform& Transform)
{
	return UnrealToUsd::ConvertXformable(Transform, Prim.InternalPrim, 0.0);
}

bool UUSDScriptingBPLibrary::ConvertStaticMesh(FUsdScriptingPrim Prim, const UStaticMesh* StaticMesh)
{
	if (!StaticMesh || !Prim.InternalPrim) return false;
	return UnrealToUsd::ConvertStaticMesh(StaticMesh, Prim.InternalPrim);
}

void UUSDScriptingBPLibrary::AddReference(FUsdScriptingPrim Prim, const FString& AbsoluteFilePath)
{
	UsdUtils::AddReference(Prim.InternalPrim, *AbsoluteFilePath);
}

void UUSDScriptingBPLibrary::AddPayload(FUsdScriptingPrim Prim, const FString& AbsoluteFilePath)
{
	UsdUtils::AddPayload(Prim.InternalPrim, *AbsoluteFilePath);
}

bool UUSDScriptingBPLibrary::SetKind(FUsdScriptingPrim Prim, EUsdScriptingKind Kind)
{
	return UsdUtils::SetDefaultKind(Prim.InternalPrim, ConvertKind(Kind));
}

EUsdDefaultKind UUSDScriptingBPLibrary::ConvertKind(EUsdScriptingKind Kind)
{
	switch (Kind)
	{
	default:
	case EUsdScriptingKind::None:
		return EUsdDefaultKind::None;
	case EUsdScriptingKind::Model:
		return EUsdDefaultKind::Model;
	case EUsdScriptingKind::Component:
		return EUsdDefaultKind::Component;
	case EUsdScriptingKind::Group:
		return EUsdDefaultKind::Group;
	case EUsdScriptingKind::Assembly:
		return EUsdDefaultKind::Assembly;
	case EUsdScriptingKind::Subcomponent:
		return EUsdDefaultKind::Subcomponent;
	}
}
