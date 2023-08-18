// Copyright (C) 2023 Broken Desk / ISHIN

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RealtimeDelayBPLibrary.generated.h"

UCLASS()
class URealtimeDelayBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Realtime Delay", meta = (Latent, WorldContext = "WorldContextObject", DisplayName = "Realtime Delay", LatentInfo = "LatentInfo", Duration = "0.2", Keywords = "sleep"))
	static void	RealtimeDelay(const UObject* WorldContextObject, float Duration, struct FLatentActionInfo LatentInfo);
};
