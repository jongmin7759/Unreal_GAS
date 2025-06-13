# Unreal_GAS

### Udemy의 GameAbilitySystem 강의 학습용 리포지터리입니다.


강의 내용은 [개인 블로그에서 섹션마다 정리하여 업로드 중입니다](https://velog.io/@jongmin7759/series/Udemy-Unreal-GAS)
</br>
</br>


## 📌색인 (헤더 파일로 연결)

### UI - MVC 패턴
- [WidgetController_Base](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/UI/WidgetController/AuraWidgetController.h)
- [OverlayWidgetController](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/UI/WidgetController/OverlayWidgetController.h)
- [UserWidget](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/UI/Widget/AuraUserWidget.h)
- [HUD](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/UI/HUD/AuraHUD.h) - 컨트롤러 생성은 HUD에서 수행 중

### GameAbilitySystem
- [AttributeSet](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/AbilitySystem/AuraAttributeSet.h)
- [AbilitySystemComponent](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/AbilitySystem/AuraAbilitySystemComponent.h)
- [PlayerState](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/Player/AuraPlayerState.h) - 플레이어용 AbilitySystemComponent는 여기서 생성
- [EnemyCharacter](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/Character/AuraEnemy.h) - 적 캐릭터는 생성자에서 바로 생성

### GameplayEffect
- [EffectActor](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/Actor/AuraEffectActor.h)
- [MMC](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/AbilitySystem/ModMagCalc/MMC_MaxHealth.h) - 게임플레이 이펙트 모디파이어의 Custom Calculator

### Interface
- [Highlight](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/Interaction/EnemyInterface.h)
- [CombatLevel](https://github.com/jongmin7759/Unreal_GAS/blob/main/Source/Aura/Public/Interaction/CombatInterface.h)
