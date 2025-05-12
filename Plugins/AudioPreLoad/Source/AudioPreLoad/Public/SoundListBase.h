#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SoundListBase.generated.h"

/**
 * Базовый абстрактный класс для списка звуков
 */
UCLASS(BlueprintType, Abstract)
class AUDIOPRELOAD_API USoundListBase : public UDataAsset
{
	GENERATED_BODY()

public:

	/** Конструктор класса */
	USoundListBase();

	/** Метод для загрузки списка звуков в кэш */
	UFUNCTION(BlueprintCallable)
	virtual void PreLoadSoundList() {}

	/** Метод для освобождения списка звуков из кэша, чтобы они могли выгрузиться из кэша */
	UFUNCTION(BlueprintCallable)
	virtual void ReleaseSoundList() {}
};
