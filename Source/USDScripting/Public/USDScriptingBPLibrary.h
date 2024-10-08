// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "USDScriptingBPLibrary.generated.h"

class UDirectionalLightComponent;
enum class EUsdDefaultKind;
enum class EUsdScriptingKind:uint8;
struct FUsdScriptingStage;
struct FUsdScriptingLayer;
struct FUsdScriptingPrim;

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UUSDScriptingBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="USD Scripting|Stage", BlueprintCallable)
	static FUsdScriptingStage NewStage();

	UFUNCTION(Category="USD Scripting|Stage", BlueprintCallable)
	static FUsdScriptingStage StageOpenLayer(FUsdScriptingLayer Layer);

	UFUNCTION(Category="USD Scripting|Stage", BlueprintCallable)
	static FUsdScriptingLayer GetRootLayer(FUsdScriptingStage Stage);

	UFUNCTION(Category="USD Scripting|Stage", BlueprintCallable)
	static bool ExportFlattened(FUsdScriptingStage Stage, const FString& FilePath);

	UFUNCTION(Category="USD Scripting|Stage", BlueprintCallable)
	static FUsdScriptingPrim DefinePrim(
		FUsdScriptingStage Stage,
		const FString& PrimPath,
		const FString& PrimType = "");

	UFUNCTION(Category="USD Scripting|Stage", BlueprintCallable)
	static void SetDefaultPrim(FUsdScriptingStage Stage, FUsdScriptingPrim Prim);
	
	UFUNCTION(Category="USD Scripting|Layer", BlueprintCallable)
	static FUsdScriptingLayer LayerFindOrOpen(const FString& Identifier, bool& bSuccess);
	
	UFUNCTION(Category="USD Scripting|Layer", BlueprintCallable)
	static FUsdScriptingLayer LayerCreateNew(const FString& Identifier);

	UFUNCTION(Category="USD Scripting|Layer", BlueprintCallable)
	static FString GetLayerIdentifier(FUsdScriptingLayer Layer);

	UFUNCTION(Category="USD Scripting|Layer", BlueprintCallable)
	static void LayerClear(FUsdScriptingLayer Layer);

	UFUNCTION(Category="USD Scripting|Layer", BlueprintCallable)
	static bool LayerSave(FUsdScriptingLayer Layer, bool bForce = false);

	UFUNCTION(Category="USD Scripting|Prim", BlueprintCallable)
	static bool ConvertDirectionalLightComponent(FUsdScriptingPrim Prim, const UDirectionalLightComponent* DirectionalLightComponent);

	UFUNCTION(Category="USD Scripting|Prim", BlueprintCallable)
	static bool ConvertXformable(FUsdScriptingPrim Prim, const FTransform& Transform);

	UFUNCTION(Category="USD Scripting|Prim", BlueprintCallable)
	static bool ConvertStaticMesh(FUsdScriptingPrim Prim, const UStaticMesh* StaticMesh);

	UFUNCTION(Category="USD Scripting|Prim", BlueprintCallable)
	static void AddReference(FUsdScriptingPrim Prim, const FString& AbsoluteFilePath);

	UFUNCTION(Category="USD Scripting|Prim", BlueprintCallable)
	static void AddPayload(FUsdScriptingPrim Prim, const FString& AbsoluteFilePath);

	UFUNCTION(Category="USD Scripting|Prim", BlueprintCallable)
	static bool SetKind(FUsdScriptingPrim Prim, EUsdScriptingKind Kind);

	static EUsdDefaultKind ConvertKind(EUsdScriptingKind Kind);
};
