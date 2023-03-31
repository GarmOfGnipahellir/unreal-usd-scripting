// Fill out your copyright notice in the Description page of Project Settings.


#include "USDScriptingWrappers.h"


FUsdScriptingStage::FUsdScriptingStage() : InternalStage(UE::FUsdStage())
{
}

FUsdScriptingStage::FUsdScriptingStage(UE::FUsdStage InStage) : InternalStage(InStage)
{
}

FUsdScriptingLayer::FUsdScriptingLayer() : InternalLayer(UE::FSdfLayer())
{
}

FUsdScriptingLayer::FUsdScriptingLayer(UE::FSdfLayer InLayer) : InternalLayer(InLayer)
{
}

FUsdScriptingPrim::FUsdScriptingPrim() : InternalPrim(UE::FUsdPrim())
{
}

FUsdScriptingPrim::FUsdScriptingPrim(UE::FUsdPrim InPrim) : InternalPrim(InPrim)
{
}
