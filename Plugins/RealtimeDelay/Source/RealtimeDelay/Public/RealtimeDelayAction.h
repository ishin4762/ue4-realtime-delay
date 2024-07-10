// Copyright (C) 2023 Broken Desk / ISHIN

#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"
#include "Engine/LatentActionManager.h"
#include "LatentActions.h"
#include "RealtimeDelayAction.generated.h"

/**
 *
 */
class FRealtimeDelayAction
{
public:
	bool Available;
	float TimeRemaining;
	FLatentActionInfo LatentInfo;

	FRealtimeDelayAction(float Duration, const FLatentActionInfo& LatentActionInfo);
	virtual ~FRealtimeDelayAction() {}
	void UpdateOperation(float ElapsedTime, UObject* InObject);
};

/**
 *
 */
UCLASS()
class URealtimeDelayActionManager : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

protected:
	TArray<FRealtimeDelayAction*> Actions;
	static URealtimeDelayActionManager* _Instance;

	UPROPERTY()
	TMap<int32, UObject*> CallbackObjects;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection)
	{
		_Instance = this;
	}
	virtual void Deinitialize() { }
	virtual TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(FRealtimeDelayAction, STATGROUP_Tickables); }
	virtual bool IsTickable() const { return true;  }
	virtual void Tick(float DeltaTime);

	FRealtimeDelayAction* FindExistingAction(UObject* InActionObject, int32 UUID);
	void AddDelayAction(float Duration, const FLatentActionInfo& LatentActionInfo);
	
	static URealtimeDelayActionManager* GetInstance()
	{
		return _Instance;
	}

};
