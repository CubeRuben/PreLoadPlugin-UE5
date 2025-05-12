#include "AudioPreLoadGlobal.h"

#include "SoundListBase.h"

AAudioPreLoadGlobal::AAudioPreLoadGlobal() :
	SoundLists()
{ }

void AAudioPreLoadGlobal::BeginPlay()
{
	Super::BeginPlay();
	
	// Итерация всего массива списков звуков
	for (USoundListBase* const & soundList : SoundLists) 
	{
		// Проверка указателя на nullptr
		if (soundList)
		{
			// Загрузка звуков в кэш
			soundList->PreLoadSoundList();
		}
	}
}

void AAudioPreLoadGlobal::BeginDestroy()
{
	Super::BeginDestroy();

	// Итерация всего массива списков звуков
	for (USoundListBase* const& soundList : SoundLists)
	{
		// Проверка указателя на nullptr
		if (soundList)
		{
			// "Освобождение" звуков из кэша
			soundList->ReleaseSoundList();
		}
	}
}

