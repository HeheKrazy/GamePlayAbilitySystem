// Copyright HeheKrazy


#include "Actor/HKEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/HKAttributeSet.h"

AHKEffectActor::AHKEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

}

void AHKEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a Gameplay Effect. For now, using const cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
	 const UHKAttributeSet* HKAttributeSet = Cast<UHKAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UHKAttributeSet::StaticClass()));

	 UHKAttributeSet* MutableHKAttributeSet = const_cast<UHKAttributeSet*>(HKAttributeSet);
	 MutableHKAttributeSet->SetHealth(HKAttributeSet->GetHealth() + 25.f);
	 Destroy();
	}

}
void AHKEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
void AHKEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AHKEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AHKEffectActor::EndOverlap);
}
