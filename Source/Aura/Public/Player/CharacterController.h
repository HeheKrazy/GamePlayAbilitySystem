// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IOverlapInterface;

/**
 * 
 */
UCLASS()
class AURA_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterController();

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();


	TScriptInterface<IOverlapInterface> LastActor;
	TScriptInterface<IOverlapInterface> ThisActor;

};
