// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent 사용하면 ASC 불러올 수 있음
	// 내부 코드를 보면
	// 1. IAbilitySystemInterface 상속 받은 경우 : 인터페이스 구현 함수로 불러옴
	// 2. 받지 않은 경우 : AbilitySystemComponent를 찾아서 불러오는 2가지 경우 모두 대응함
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr)
	{
		return;
	}

	check(GameplayEffectClass);
	// FGameplayEffectContextHandle 만들기
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// Context에는 다양한 정보가 들어가고 Handle은 Wrapper 클래스임
	// EffectContext에 정보 추가 (이 이펙트를 발생시킨 객체 추가한 것)
	EffectContextHandle.AddSourceObject(this);
	
	// FGameplayEffectSpec 만들기
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass,ActorLevel,EffectContextHandle);

	// ApplyGameplayEffect~~ 종류 여러가지 있음
	// 인자로 EffectSpec 참조 포인터가 필요한데 EffectSpecHandle은 래퍼이고 그 안에는 Data(SharedPtr)가 들어있음
	// SharedPtr 자체도 래퍼이므로 Get하면 포인터가 나옴
	// 포인터가 아닌 그 참조값 자체가 필요하므로 * 를 붙여줌
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// Ptr->Get->Ptr->Get 해서 UGameplayEffect에 접근
	// GameplayEffectClass로 만들어진 CDO의 속성(DurationPolicy)을 확인하기 위한 것이지 동적으로 수정하거나 하려는 것은 아님
	// Infinite 타입이라면 핸들과 액터를 맵으로 저장해두기
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle,TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		// 루핑 안에서 핸들을 제거할 수는 없으니까 제거할 핸들을 모아둠
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				// Remove 인자에 -1 (기본값) 넣으면 모든 스택이 제거됨
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
		
	}
}
