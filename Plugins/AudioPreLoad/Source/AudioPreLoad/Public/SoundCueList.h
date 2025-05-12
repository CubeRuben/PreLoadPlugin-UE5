#pragma once

#include "CoreMinimal.h"
#include "SoundListBase.h"
#include "SoundCueList.generated.h"

/**
 * Класс для списка звуков типа USoundCue
 */
UCLASS(BlueprintType)
class AUDIOPRELOAD_API USoundCueList : public USoundListBase
{
	GENERATED_BODY()

public:

	/** Конструктор класса */
	USoundCueList();

protected:

	/** Массив ассетов USoundCue */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class USoundCue*> SoundList;

	/** Менять ли принудительно поведение загрузки ассетов звуков */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ForceRetainOnLoad;

	/** Метод для рекурсивного движения по узлам в USoundCue */
	void PreLoadNodes(USoundNode* Node, const class FOnSoundLoadComplete& Delegate);

	/** Метод-обратный вызов (callback) при загрузке звука в кэш */
	UFUNCTION()
	void OnSoundLoaded(const class USoundWave* LoadedSoundWave, const bool WasCancelled);

public:

	/** Геттер адреса на массив звуков */
	const TArray<class USoundCue*>& GetSoundList() const { return SoundList; }

	/** Переопределение методов из USoundListBase */
	void PreLoadSoundList() override;
	void ReleaseSoundList() override;
};
