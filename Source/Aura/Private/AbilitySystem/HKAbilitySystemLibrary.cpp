// Copyright HeheKrazy


#include "AbilitySystem/HKAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/HKHUD.h"
#include "UI/WidgetController/HKWidgetController.h"
#include "Player/MyPlayerState.h"
#include "Game/MyGameModeBase.h"
#include "AbilitySystemComponent.h"
#include "HKAbilityTypes.h"
#include "Interaction/CombatInterface.h"

UOverlayWidgetController* UHKAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AHKHUD* HKHUD = Cast<AHKHUD>(PC->GetHUD()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return HKHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UHKAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AHKHUD* HKHUD = Cast<AHKHUD>(PC->GetHUD()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return HKHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UHKAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultsInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);


	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultsInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UHKAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UCharacterClassInfo* UHKAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AMyGameModeBase* HKGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (HKGameMode == nullptr) return nullptr;

	return HKGameMode->CharacterClassInfo;

}

bool UHKAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FHKGameplayEffectContext* HKEffectContext = static_cast<const FHKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HKEffectContext->IsBlockedHit();
	}
	return false;
}

bool UHKAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FHKGameplayEffectContext* HKEffectContext = static_cast<const FHKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HKEffectContext->IsCriticalHit();
	}
	return false;
}

void UHKAbilitySystemLibrary::SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle EffectContextHandle, bool bInIsBlockedHit)
{
	if (FHKGameplayEffectContext* HKEffectContext = static_cast<FHKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HKEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UHKAbilitySystemLibrary::SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle EffectContextHandle, bool bInIsCriticalHit)
{
	if (FHKGameplayEffectContext* HKEffectContext = static_cast<FHKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HKEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}
