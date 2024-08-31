// Copyright HeheKrazy


#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/HKAbilitySystemComponent.h"
#include "Player/MyPlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/HUD/HKHUD.h"
#include "AbilitySystem/Data/LevelupInfo.h"


APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterClass = ECharacterClass::Elementalist;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init AbilityActorInfo for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

int32 APlayerCharacter::GetPlayerLevel_Implementation()
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->GetPlayerLevel();
}

void APlayerCharacter::LevelUp_Implementation()
{
}

int32 APlayerCharacter::GetXP_Implementation() const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->GetXP();
}

int32 APlayerCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->LevelUpInfo->FindLevelForXp(InXP);
}

int32 APlayerCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);

	return MyPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
}

int32 APlayerCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);

	return MyPlayerState->LevelUpInfo->LevelUpInformation[Level].SpellPointAward;
}

void APlayerCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);

	MyPlayerState->AddToLevel(InPlayerLevel);
}

void APlayerCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
}

void APlayerCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);

}

void APlayerCharacter::AddToXP_Implementation(int32 InXP)
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->AddToXP(InXP);
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);

	Cast<UHKAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();

	if (APlayerController* HKPlayerController = Cast<APlayerController>(GetController()))
	{
		if (AHKHUD* HKHUD = Cast<AHKHUD>(HKPlayerController->GetHUD()))
		{
			HKHUD->InitOverlay(HKPlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefualtAttributes();
}
