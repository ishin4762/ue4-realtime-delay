// Copyright (C) 2023 Broken Desk / ISHIN


#include "RealtimeDelayAction.h"

URealtimeDelayActionManager* URealtimeDelayActionManager::_Instance = nullptr;

FRealtimeDelayAction::FRealtimeDelayAction(float Duration, const FLatentActionInfo& LatentActionInfo)
	: Available(true)
	, TimeRemaining(Duration)
	, LatentInfo(LatentActionInfo)
{
}

void FRealtimeDelayAction::UpdateOperation(float ElapsedTime)
{
	if (Available) {
		TimeRemaining -= ElapsedTime;
		if (TimeRemaining <= 0.0f) {
			Available = false;
			if (LatentInfo.Linkage != INDEX_NONE)
			{
				if (UObject* CallbackTarget = LatentInfo.CallbackTarget)
				{
					if (UFunction* ExecutionFunction = CallbackTarget->FindFunction(LatentInfo.ExecutionFunction))
					{
						CallbackTarget->ProcessEvent(ExecutionFunction, &(LatentInfo.Linkage));
					}
					else
					{
						UE_LOG(LogScript, Warning, TEXT("FRealtimeDelayAction::UpdateOperation: Could not find latent action resume point named '%s' on '%s'"),
							*LatentInfo.ExecutionFunction.ToString(), *(CallbackTarget->GetPathName()));
					}
				}
				else
				{
					UE_LOG(LogScript, Warning, TEXT("FRealtimeDelayAction::UpdateOperation: CallbackTarget is None."));
				}
			}
		}

	}
}

void URealtimeDelayActionManager::Tick(float DeltaTime)
{
	// Execute
	for (int32 Index = 0; Index < Actions.Num(); Index++)
	{
		Actions[Index]->UpdateOperation(DeltaTime);
	}

	// Delete Old event
	int32 DeleteIndex = -1;
	while (DeleteIndex >= 0)
	{
		DeleteIndex = -1;
		for (int32 Index = 0; Index < Actions.Num(); Index++)
		{
			if (!Actions[Index]->Available && Actions.IsValidIndex(Index))
			{
				DeleteIndex = Index;
				break;
			}
		}
		if (DeleteIndex >= 0) {
			delete Actions[DeleteIndex];
			Actions.RemoveAt(DeleteIndex);
		}
	}
}


FRealtimeDelayAction* URealtimeDelayActionManager::FindExistingAction(UObject* InActionObject, int32 UUID)
{
	for (int32 Index = 0; Index < Actions.Num(); Index++)
	{
		if (Actions[Index]->LatentInfo.CallbackTarget == InActionObject
			&& Actions[Index]->LatentInfo.UUID == UUID
			&& Actions[Index]->Available)
		{
			return Actions[Index];
		}
	}

	return nullptr;
}

void URealtimeDelayActionManager::AddDelayAction(float Duration, const FLatentActionInfo& LatentActionInfo)
{
	Actions.Add(new FRealtimeDelayAction(Duration, LatentActionInfo));
}
