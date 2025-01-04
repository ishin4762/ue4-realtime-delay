// Copyright (C) 2023 Broken Desk / ISHIN


#include "RealtimeDelayAction.h"

URealtimeDelayActionManager* URealtimeDelayActionManager::_Instance = nullptr;

FRealtimeDelayAction::FRealtimeDelayAction(float Duration, const FLatentActionInfo& LatentActionInfo)
	: Available(true)
	, IsFirstOperation(true)
	, TimeRemaining(Duration)
	, LatentInfo(LatentActionInfo)
{
}

void FRealtimeDelayAction::UpdateOperation(float ElapsedTime, UObject* InObject)
{
	if (Available)
	{
		TimeRemaining -= ElapsedTime;
		if (TimeRemaining <= 0.0f && !IsFirstOperation)
		{
			Available = false;
			if (LatentInfo.Linkage != INDEX_NONE)
			{
				if (UObject* CallbackTarget = LatentInfo.CallbackTarget)
				{
					if (!IsValid(InObject) || InObject != CallbackTarget)
					{
						// Callback object has already been destroyed.
						return;
					}

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

		if (IsFirstOperation)
		{
			IsFirstOperation = false;
		}

	}
}

void URealtimeDelayActionManager::Tick(float DeltaTime)
{
	// Execute
	for (int32 Index = 0; Index < Actions.Num(); Index++)
	{
		int32 UUID = Actions[Index]->LatentInfo.UUID;
		Actions[Index]->UpdateOperation(DeltaTime, CallbackObjects[UUID]);
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
			int32 UUID = Actions[DeleteIndex]->LatentInfo.UUID;
			delete Actions[DeleteIndex];
			Actions.RemoveAt(DeleteIndex);
			CallbackObjects.Remove(UUID);
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
	CallbackObjects.Add(LatentActionInfo.UUID, LatentActionInfo.CallbackTarget);
}
