#pragma once

#include "CoreMinimal.h"
#include "SoundListBase.h"
#include "SoundWaveList.generated.h"

/**
 * Класс для списка звуков типа USoundWave
 */
UCLASS(BlueprintType)
class AUDIOPRELOAD_API USoundWaveList : public USoundListBase
{
	GENERATED_BODY()

public:

	/** Конструктор класса */
	USoundWaveList();

protected:
	
	/** Массив ассетов USoundWave */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class USoundWave*> SoundList;

	/** Менять ли принудительно поведение загрузки ассетов звуков */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ForceRetainOnLoad;

	/** Метод-обратный вызов (callback) при загрузке звука в кэш */
	UFUNCTION()
	void OnSoundLoaded(const class USoundWave* LoadedSoundWave, const bool WasCancelled);

public:

	/** Геттер адреса на массив звуков */
	const TArray<class USoundWave*>& GetSoundList() const { return SoundList; }

	/** Переопределение методов из USoundListBase */
	void PreLoadSoundList() override;
	void ReleaseSoundList() override;
};
