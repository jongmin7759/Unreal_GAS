// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

// 1. 생성자 만들기
// 2. 계산 함수(CalculateBaseMagnitude_Implementation) 오버라이드
// 3. 필요한 Attribute 캡처(FGameplayEffectAttributeCaptureDefinition)
//	3-1. 생성자에서 ACCESSOR 매크로 통해 MyAttributeSet에 만들어진 함수로 할당 (AttributeToCapture) - 어떤 Attribute 캡처할지
//	3-2. 해당 Attribute를 이펙트의 Source에서 받아올지, Target에서 받아올지 지정
//	3-3. 스냅샷 여부 설정
// 4. RelevantAttributesToCapture에 캡처할 Attribute 추가하기
// 5. GetCapturedAttributeMagnitude로 원하는 Attribute의 값을 받아오고
// 6. 원하는 값으로 조정한 뒤 CalculateBaseMagnitude_Implementation의 결과로 리턴

UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_MaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
