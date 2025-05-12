#include "SoundCueList.h"

#include "AudioPreLoadLog.h"

#include <Sound/SoundNodeWavePlayer.h>
#include <Sound/SoundCue.h>
#include <AudioMixerBlueprintLibrary.h>

USoundCueList::USoundCueList() :
	SoundList(),
	ForceRetainOnLoad(true)
{ }

void USoundCueList::PreLoadNodes(USoundNode* Node, const FOnSoundLoadComplete& Delegate)
{
	// Итерация всего массива дочерних узлов
	for (USoundNode* childNode : Node->ChildNodes)
	{
		// Проверка указателя на nullptr
		if (!childNode)
		{
			// Переход на следующий шаг цикла
			continue;
		}

		childNode->ConditionalPostLoad();
		// Рекурсивный вызов 
		PreLoadNodes(childNode, Delegate);
	}

	// Каст узла в USoundNodeWavePlayer
	USoundNodeWavePlayer* const wavePlayer = Cast<USoundNodeWavePlayer>(Node);
	// Проверка указателя на nullptr
	if (!wavePlayer)
	{
		return;
	}

	// Получение USoundWave из USoundNodeWavePlayer
	USoundWave* const soundWave = wavePlayer->GetSoundWave();
	// Проверка указателя на nullptr
	if (!soundWave)
	{
		return;
	}

	// Проверка необходимости переопределения поведения загрузки ассета
	if (ForceRetainOnLoad) 
	{
		// Переопределение поведения загрузка ассета
		soundWave->OverrideLoadingBehavior(ESoundWaveLoadingBehavior::RetainOnLoad);
	}
	
	// Загрузка звука в кэш
	UAudioMixerBlueprintLibrary::PrimeSoundForPlayback(soundWave, Delegate);
}

void USoundCueList::PreLoadSoundList()
{
	// Создание делегата для обратного вызова
	FOnSoundLoadComplete onSoundLoadedDelegate;
	// Привязка метода
	onSoundLoadedDelegate.BindDynamic(this, &USoundCueList::OnSoundLoaded);

	// Итерация всего массива звуков
	for (USoundCue* const& soundCue : SoundList)
	{
		// Проверка указателя на nullptr
		if (!soundCue)
		{
			// Переход на следующий шаг цикла
			continue;
		}

		// Проверка указателя FirstNode на nullptr
		if (soundCue->FirstNode) 
		{
			// Запуск поиска звуков в SoundCue
			PreLoadNodes(soundCue->FirstNode, onSoundLoadedDelegate);
		}
	}
}

void USoundCueList::ReleaseSoundList()
{
	// Итерация всего массива звуков
	for (USoundCue* const& soundCue : SoundList)
	{
		// Проверка указателя на nullptr
		if (soundCue)
		{
			// "Освобождение" звука для будущего удаления из кэша
			soundCue->ReleaseRetainedAudio();
		}
	}
}

void USoundCueList::OnSoundLoaded(const USoundWave* LoadedSoundWave, const bool WasCancelled)
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