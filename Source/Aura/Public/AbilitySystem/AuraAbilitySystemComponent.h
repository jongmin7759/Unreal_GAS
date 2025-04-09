// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

// BP에서 바인딩하지 않고 WidgetController에 바인딩할 것이므로 Dynamic X
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	// 이 함수는 캐릭터에서 InitAbilityActor 이후에 호출하게됨 -> ASC는 캐릭터로부터 독립적이고 캐릭터만 ASC에 의존하게 됨 (일방향 의존성 유지)
	void AbilityActorInfoSet();

	// Controller에서 바인딩할 수 있도록 Public 섹션에
	FEffectAssetTags EffectAssetTags;
	
protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
