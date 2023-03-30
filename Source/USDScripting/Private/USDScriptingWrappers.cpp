// Fill out your copyright notice in the Description page of Project Settings.


#include "USDScriptingWrappers.h"


FUsdScriptingStage::FUsdScriptingStage()
{
}

FUsdScriptingStage::FUsdScriptingStage(UE::FUsdStage InStage): InternalStage(InStage)
{
}

FUsdScriptingPrim::FUsdScriptingPrim()
{
}

FUsdScriptingPrim::FUsdScriptingPrim(UE::FUsdPrim InPrim) : InternalPrim(InPrim)
{
}
