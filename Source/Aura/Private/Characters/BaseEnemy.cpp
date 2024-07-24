// Copyright HeheKrazy


#include "Characters/BaseEnemy.h"
#include "AbilitySystem/HKAbilitySystemComponent.h"
#include "AbilitySystem/HKAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/HKAbilitySystemLibrary.h"
#include "UI/Widget/HKUserWidget.h"
#include "HKGameplayTags.h"
#include "AI/HKAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UHKAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;	
	AttributeSet = CreateDefaultSubobject<UHKAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ABaseEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	HKAIController = Cast<AHKAIController>(NewController);
	HKAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	HKAIController->RunBehaviorTree(BehaviorTree);
}



void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UHKAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}

	if (UHKUserWidget* HKUserWidget = Cast<UHKUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		HKUserWidget->SetWidgetController(this);
	}
	

	if (const UHKAttributeSet* HKAS = Cast<UHKAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HKAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HKAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
		
		AbilitySystemComponent->RegisterGameplayTagEvent(FHKGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ABaseEnemy::HitReactTagChanged

		);

		OnHealthChanged.Broadcast(HKAS->GetHealth());
		OnMaxHealthChanged.Broadcast(HKAS->GetMaxHealth());
	}
	
}
void ABaseEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void ABaseEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UHKAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefualtAttributes();
	}
	
}

void ABaseEnemy::InitializeDefualtAttributes() const
{
	UHKAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void ABaseEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ABaseEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 ABaseEnemy::GetPlayerLevel()
{
	return Level;
}

void ABaseEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}
