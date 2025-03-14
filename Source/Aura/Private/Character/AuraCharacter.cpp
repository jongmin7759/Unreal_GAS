// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "SAdvancedTransformInputBox.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	// 탑다운 뷰로 진행되는 게임이므로 카메라는 고정되어있고 입력 방향에 따라 캐릭터가 회전하도록 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// 캐릭터가 바닥에 붙어있도록 설정
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 서버 전용
	//if (HasAuthority()) 체크 안 해도 되는 게 이미 Server에서만 호출되는 함수임
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// 클라이언트 전용
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* PlayerState = GetPlayerState<AAuraPlayerState>(); // 템플릿 버전이 있음
	check(PlayerState);
	AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(PlayerState, this);
	AttributeSet = PlayerState->GetAttributeSet();
}
