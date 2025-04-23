// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	// MaxHealth의 경우 플레이어 캐릭터가 스탯 초기화할 때 사용하고 있으므로 Source == Target
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	// Attribute의 기준점을 어느 시기로 할 것인가.
	// True : EffectSpec이 생성되자마자 , False : Effect의 적용 시점에
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	// Source와 Target의 태그 정보 접근 가능
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Vigor는 OutParam
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluationParameters,Vigor);
	// 클램핑 (0보다 낮아지지 않도록)
	Vigor = FMath::Max<float>(Vigor,0.f);

	// Source 오브젝트 받아오기 (이 경우 AuraCharacter의 레벨을 알아내기 위함)
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetCombatLevel();
	
	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
