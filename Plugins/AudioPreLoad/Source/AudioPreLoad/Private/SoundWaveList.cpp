#include "SoundWaveList.h"

#include "AudioPreLoadLog.h"

#include <Sound/SoundWave.h>
#include <AudioMixerBlueprintLibrary.h>

USoundWaveList::USoundWaveList() :
	SoundList(),
	ForceRetainOnLoad(true)
{ }

void USoundWaveList::PreLoadSoundList()
{
	// Создание делегата для обратного вызова
	FOnSoundLoadComplete onSoundLoadedDelegate;
	// Привязка метода
	onSoundLoadedDelegate.BindDynamic(this, &USoundWaveList::OnSoundLoaded);

	// Итерация всего массива звуков
	for (USoundWave* const& soundWave : SoundList)
	{
		// Проверка указателя на nullptr
		if (!soundWave)
		{
			// Переход на следующий шаг цикла
			continue;
		}

		// Проверка необходимости переопределения поведения загрузки ассета
		if (ForceRetainOnLoad)
		{
			// Переопределение поведения загрузка ассета
			soundWave->OverrideLoadingBehavior(ESoundWaveLoadingBehavior::RetainOnLoad);
		}

		// Загрузка звука в кэш
		UAudioMixerBlueprintLibrary::PrimeSoundForPlayback(soundWave, onSoundLoadedDelegate);
	}
}

void USoundWaveList::ReleaseSoundList()
{
	// Итерация всего массива звуков
	for (USoundWave* const& soundWave : SoundList)
	{
		// Проверка указателя на nullptr
		if (soundWave)
		{
			// "Освобождение" звука для будущего удаления из кэша
			soundWave->ReleaseCompressedAudio();
		}
	}
}

void USoundWaveList::OnSoundLoaded(const USoundWave* LoadedSoundWave, const bool WasCancelled)
{
	// Проверка указателя на nullptr
	if (!LoadedSoundWave)
		return;

	// Получение названия ассета звука
	FString soundName;
	LoadedSoundWave->GetName(soundName);

	if (WasCancelled)
	{
		// Вывод в консоль, если возникла ошибка
		UE_LOG(LogAudioPreLoad, Log, TEXT("An error occurred during preload of: %s"), *soundName);
	}
	else
	{
		// Вывод в консоль, если загрузка была успешной
		UE_LOG(LogAudioPreLoad, Log, TEXT("Successfully preloaded: %s"), *soundName);
	}
}