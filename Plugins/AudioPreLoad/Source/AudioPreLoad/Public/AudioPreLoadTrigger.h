#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioPreLoadTrigger.generated.h"

/**
 * Actor, который предзагружает звуки при заходе игрока в определенную область
 */
UCLASS()
class AUDIOPRELOAD_API AAudioPreLoadTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

	/** Конструктор класса */
	AAudioPreLoadTrigger();

protected:

	/** Компонент триггер */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* TriggerComponent;

	/** Массив списков звуков */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<class USoundListBase>> SoundLists;

	/** Метод, вызываемый при старте уровня */
	virtual void BeginPlay() override;

	/** Метод, вызываемый при уничтожении актора/завершении уровня */
	virtual void BeginDestroy() override;

	/** Метод, вызываемый при входе другого актора в триггер */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/** Метод, вызываемый при выходе другого актора из триггера */
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
