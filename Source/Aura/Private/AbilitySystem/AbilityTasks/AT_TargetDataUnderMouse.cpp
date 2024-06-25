


#include "AbilitySystem/AbilityTasks/AT_TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UAT_TargetDataUnderMouse* UAT_TargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UAT_TargetDataUnderMouse* MyObj = NewAbilityTask<UAT_TargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UAT_TargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if (bIsLocallyControlled)
	{
		//SendTargetDataToServer ;
		SendMouseCursorData();
	}
	else
	{
		// ReceiveTargetDataFromClient ;

		
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UAT_TargetDataUnderMouse::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);


		//If the target data has NOT arrived, tell the server that it needs to wait for player data that will eventually arrive for the cliente
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UAT_TargetDataUnderMouse::SendMouseCursorData() const
{
	/* Because down below we are using the ability system's ScopedPredicitionKey variable,
	 * we first need to update it. To do this, we call the following function, in order to tell the
	 * server that everything we do here locally is going to be predicted. It's scoped because it means
	 * that the prediction will only occur in the place where we use the variable
	 **/
	
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UAT_TargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
