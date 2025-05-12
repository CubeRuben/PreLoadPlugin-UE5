#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioPreLoadGlobal.generated.h"

/**
 * Actor, который предзагружает звуки при загрузке уровня
 */
UCLASS(BlueprintType)
class AUDIOPRELOAD_API AAudioPreLoadGlobal : public AActor
{
	GENERATED_BODY()
	
public:	

	/** Конструктор класса */
	AAudioPreLoadGlobal();

protected:

	/** Массив списков звуков */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<class USoundListBase>> SoundLists;

	/** Метод, вызываемый при старте уровня */
	virtual void BeginPlay() override;

	/** Метод, вызываемый при уничтожении актора/завершении уровня */
	virtual void BeginDestroy() override;
};
