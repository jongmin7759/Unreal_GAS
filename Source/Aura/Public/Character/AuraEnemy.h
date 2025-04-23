// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public  IEnemyInterface // 인터페이스 상속
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	// EnemyInterface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// end EnemyInterface

	// CombatInterface
	virtual int32 GetCombatLevel() override;
	// end CombatInterface
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	// 적 캐릭터의 레벨은 리플리케이션 할 필요 없이 서버에서만 계산할 예정임 
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	int32 Level = 1;

};
