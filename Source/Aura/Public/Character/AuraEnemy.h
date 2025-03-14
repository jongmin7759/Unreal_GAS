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
	
protected:
	virtual void BeginPlay() override;
};
