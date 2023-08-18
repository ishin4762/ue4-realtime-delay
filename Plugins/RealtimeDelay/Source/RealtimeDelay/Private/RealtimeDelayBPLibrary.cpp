// Copyright (C) 2023 Broken Desk / ISHIN

#include "RealtimeDelayBPLibrary.h"
#include "RealtimeDelay.h"
#include "RealtimeDelayAction.h"

URealtimeDelayBPLibrary::URealtimeDelayBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void URealtimeDelayBPLibrary::RealtimeDelay(const UObject* WorldContextObject, float Duration, FLatentActionInfo LatentInfo)
{
	if (URealtimeDelayActionManager::GetInstance()->FindExistingAction(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
	{
		URealtimeDelayActionManager::GetInstance()->AddDelayAction(Duration, LatentInfo);
	}
}
