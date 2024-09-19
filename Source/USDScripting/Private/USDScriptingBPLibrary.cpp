// Copyright Epic Games, Inc. All Rights Reserved.

#include "USDScriptingBPLibrary.h"
#include "USDScripting.h"
#include "USDScriptingWrappers.h"
#include "UnrealUSDWrapper.h"
#include "USDConversionUtils.h"
#include "USDGeomMeshConversion.h"
#include "USDPrimConversion.h"
#include "USDLightConversion.h"
#include "UsdWrappers/SdfPath.h"

#include "USDIncludesStart.h"
#include "pxr/usd/usdLux/distantLight.h"
#include "USDIncludesEnd.h"

FUsdScriptingStage UUSDScriptingBPLibrary::NewStage()
{
	return FUsdScriptingStage(UnrealUSDWrapper::NewStage());
}

FUsdScriptingStage UUSDScriptingBPLibrary::StageOpenLayer(FUsdScriptingLayer Layer)
{
	return FUsdScriptingStage(
		UnrealUSDWrapper::OpenStage(Layer.Internal, UE::FSdfLayer(), EUsdInitialLoadSet::LoadAll)
	);
}

FUsdScriptingLayer UUSDScriptingBPLibrary::GetRootLayer(FUsdScriptingStage Stage)
{
	return FUsdScriptingLayer(Stage->GetRootLayer());
}

bool UUSDScriptingBPLibrary::ExportFlattened(FUsdScriptingStage Stage, const FString& FilePath)
{
	return Stage->Export(*FilePath);
}

FUsdScriptingPrim UUSDScriptingBPLibrary::DefinePrim(
	FUsdScriptingStage Stage,
	const FString& PrimPath,
	const FString& PrimType
)
{
	return FUsdScriptingPrim(Stage->DefinePrim(UE::FSdfPath{*PrimPath}, *PrimType));
}

void UUSDScriptingBPLibrary::SetDefaultPrim(FUsdScriptingStage Stage, FUsdScriptingPrim Prim)
{
	Stage->SetDefaultPrim(Prim.Internal);
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
	return Layer->GetIdentifier();
}

void UUSDScriptingBPLibrary::LayerClear(FUsdScriptingLayer Layer)
{
	Layer->Clear();
}

bool UUSDScriptingBPLibrary::LayerSave(FUsdScriptingLayer Layer, bool bForce)
{
	return Layer->Save(bForce);
}

bool UUSDScriptingBPLibrary::ConvertDirectionalLightComponent(
	FUsdScriptingPrim Prim,
	const UDirectionalLightComponent*
	DirectionalLightComponent
)
{
	if (!Prim.Internal)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("ConvertDirectionalLightComponent: Invalid prim: %s"),
			*Prim->GetPrimPath().GetString()
		)
		return false;
	}

	if (!Prim->SetTypeName("DistantLight"))
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("ConvertDirectionalLightComponent: Can't define distant light for prim: %s"),
			*Prim->GetPrimPath().GetString()
		)
		return false;
	}

	pxr::UsdLuxDistantLight Light{Prim.Internal};
	if (!Light)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("ConvertDirectionalLightComponent: Can't cast to distant light prim: %s"),
			*Prim->GetPrimPath().GetString()
		)
		return false;
	}

	return UnrealToUsd::ConvertDirectionalLightComponent(*DirectionalLightComponent, Prim.Internal);
}

bool UUSDScriptingBPLibrary::ConvertXformable(FUsdScriptingPrim Prim, const FTransform& Transform)
{
	return UnrealToUsd::ConvertXformable(Transform, Prim.Internal, UsdUtils::GetDefaultTimeCode());
}

bool UUSDScriptingBPLibrary::ConvertStaticMesh(FUsdScriptingPrim Prim, const UStaticMesh* StaticMesh)
{
	if (!StaticMesh || !Prim.Internal) return false;
	return UnrealToUsd::ConvertStaticMesh(StaticMesh, Prim.Internal);
}

void UUSDScriptingBPLibrary::AddReference(FUsdScriptingPrim Prim, const FString& AbsoluteFilePath)
{
	UsdUtils::AddReference(Prim.Internal, *AbsoluteFilePath);
}

void UUSDScriptingBPLibrary::AddPayload(FUsdScriptingPrim Prim, const FString& AbsoluteFilePath)
{
	UsdUtils::AddPayload(Prim.Internal, *AbsoluteFilePath);
}

bool UUSDScriptingBPLibrary::SetKind(FUsdScriptingPrim Prim, EUsdScriptingKind Kind)
{
	return UsdUtils::SetDefaultKind(Prim.Internal, ConvertKind(Kind));
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
