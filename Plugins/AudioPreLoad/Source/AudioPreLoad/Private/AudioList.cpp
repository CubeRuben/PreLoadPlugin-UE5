#include "AudioList.h"

#include <AudioMixerBlueprintLibrary.h>

DEFINE_LOG_CATEGORY(LogAudioPreLoad);

UAudioList::UAudioList() :
	SoundList(),
	ForceRetainOnLoad(true)
{ }

void UAudioList::PreLoadSoundList()
{
	FOnSoundLoadComplete onSoundLoadedDelegate;
	onSoundLoadedDelegate.BindDynamic(this, &UAudioList::OnSoundLoaded);

	for (USoundWave* const & soundWave : SoundList) 
	{
		if (!soundWave)
		{ 
			continue;
		}

		if (ForceRetainOnLoad)
		{
			soundWave->LoadingBehavior = ESoundWaveLoadingBehavior::RetainOnLoad;
		}

		UAudioMixerBlueprintLibrary::PrimeSoundForPlayback(soundWave, onSoundLoadedDelegate);
	}
}

void UAudioList::OnSoundLoaded(const USoundWave* LoadedSoundWave, const bool WasCancelled)
{
	if (!LoadedSoundWave)
		return;

	FString logMessage;
	LoadedSoundWave->GetName(logMessage);

	if (WasCancelled)
	{
		UE_LOG(LogAudioPreLoad, Log, TEXT("An error occurred during preload of: %s"), *logMessage);
	}
	else 
	{
		UE_LOG(LogAudioPreLoad, Log, TEXT("Successfully preloaded: %s"), *logMessage);
	}
}