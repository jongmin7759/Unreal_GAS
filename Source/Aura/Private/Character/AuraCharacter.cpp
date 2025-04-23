// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

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

int32 AAuraCharacter::GetCombatLevel()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); 
	check(AuraPlayerState);
	return AuraPlayerState->GetCombatLevel();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); // 템플릿 버전이 있음
	check(AuraPlayerState);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	// AbilityActorInfo가 설정된 이후 호출되도록 순서제어 - 여기서 델리게이트 바인딩함
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet(); 
	AttributeSet = AuraPlayerState->GetAttributeSet();

	// InitOverlay
	// 멀티플레이어의 경우 플레이어블 캐릭터가 항상 Playercontroller를 들고있지는 않기때문에 ValidCheck을 하고 넘어가면
	// 다른 클라이언트가 컨트롤 중인 플레이어 캐릭터에서 ASSERT가 발생할 수 있기때문에 if()로 valid 확인된 경우만 Init해주면 됨
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
	// check(PlayerController) X , 마찬가지로 HUD도 1 플레이어한테만 있으니까 if() 체크만 하기
		if (AAuraHUD* AuraHUD = PlayerController->GetHUD<AAuraHUD>())
		{
			AuraHUD->InitOverlay(PlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}

	// ASC가 세팅된 이후에 어트리뷰트 초기화 불러오기
	// Attribute가 모두 리플리케이션되기때문에 서버에서만 불러와도 상관없음
	InitializeDefaultAttributes();
}
