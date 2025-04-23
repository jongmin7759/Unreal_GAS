// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:
	// 인터페이스 받고있으면서 레벨이 필요없는 캐릭터도 있을테니까 순수가상함수 대신 기본 0 리턴하도록 해둠
	virtual int32 GetCombatLevel();
};
