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
	FOnSoundLoadComplete onSoundLoadedDelegate;
	onSoundLoadedDelegate.BindDynamic(this, &USoundWaveList::OnSoundLoaded);

	for (USoundWave* const& soundWave : SoundList)
	{
		if (!soundWave)
		{
			continue;
		}

		if (ForceRetainOnLoad)
		{
			soundWave->OverrideLoadingBehavior(ESoundWaveLoadingBehavior::RetainOnLoad);
		}

		UAudioMixerBlueprintLibrary::PrimeSoundForPlayback(soundWave, onSoundLoadedDelegate);
	}
}

void USoundWaveList::ReleaseSoundList()
{
	for (USoundWave* const& soundWave : SoundList)
	{
		if (soundWave)
		{
			soundWave->ReleaseCompressedAudio();
		}
	}
}

void USoundWaveList::OnSoundLoaded(const USoundWave* LoadedSoundWave, const bool WasCancelled)
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