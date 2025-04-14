// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// AttributeSet 멤버가 확실히 할당된 이후에 브로드캐스팅된다는 것을 전제로 하므로 CastChecked 사용
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// ASC의 델리게이트 받아오기, 바인딩할 어트리뷰트 구조체를 인자로 넣기
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()) // 델리게이트 불러오고
	.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	// Effect Delegate 바인딩
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(  // 람다 함수 [capture](param){body}
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (FGameplayTag Tag : AssetTags)
			{
				// 태그가 메시지인 경우에만 메시지 델리게이트를 사용하도록 필터링
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");
				if (Tag.MatchesTag(MessageTag))
				{
					// [] 안에 this 멤버 넣어주지 않으면 람다 함수 내에서는 정보가 없어서 멤버 함수 호출을 못함.
                    // []를 통해 외부 변수를 캡쳐해서 사용한다.
                    const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
                    MessageWidgetRowDelegate.Broadcast(*Row);
				}
				
				
			}
		}
	);
}

