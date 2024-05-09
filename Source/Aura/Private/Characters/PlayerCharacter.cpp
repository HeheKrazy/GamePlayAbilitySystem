// Copyright HeheKrazy


#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Player/MyPlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/HUD/HKHUD.h"


APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init AbilityActorInfo for the Server
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();

	if (APlayerController* HKPlayerController = Cast<APlayerController>(GetController()))
	{
		if (AHKHUD* HKHUD = Cast<AHKHUD>(HKPlayerController->GetHUD()))
		{
			HKHUD->InitOverlay(HKPlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
