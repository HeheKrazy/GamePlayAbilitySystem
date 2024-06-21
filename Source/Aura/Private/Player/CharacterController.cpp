// Copyright HeheKrazy


#include "Player/CharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/HKInputComponent.h"
#include "Interaction/OverlapInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SplineComponent.h"
#include "HKGameplayTags.h"
#include "AbilitySystem/HKAbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

ACharacterController::ACharacterController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ACharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();

}
void ACharacterController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ACharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UHKInputComponent* HKInputComponent = CastChecked<UHKInputComponent>(InputComponent);
	HKInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterController::Move);

	HKInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ACharacterController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// which direction is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ACharacterController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IOverlapInterface>(CursorHit.GetActor());

	/*
	Line Trace from cursor. There are several scenarios:

	A. LastActor is null && ThisActor is null
		-Do nothing
	B. LastActor is null && ThisActor is valid
		- Highlight ThisActor
	C. LastActor is valid && ThisActor is null
		-Unhighlight LastActor
	D. Both actors are valid, but LastActor != ThisActor
		-Unhighlight LastActor, and Highlight ThisActor
	E. Both actor are valid
		-Do nothing
	*/


	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A - Both actors are null, do nothing
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // Both actors are valid
		{
			if (LastActor != ThisActor)
			{
				//Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E - Both actors are valid, do nothing
			}
		}
	}
}

void ACharacterController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FHKGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void ACharacterController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FHKGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void ACharacterController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FHKGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UHKAbilitySystemComponent* ACharacterController::GetASC()
{
	if (HKAbilitySystemComponenet == nullptr)
	{
		HKAbilitySystemComponenet = Cast<UHKAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return HKAbilitySystemComponenet;
}


