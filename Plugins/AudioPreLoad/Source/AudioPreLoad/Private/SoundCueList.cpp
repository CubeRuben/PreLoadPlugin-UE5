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
	for (USoundNode* childNode : Node->ChildNodes)
	{
		if (!childNode)
		{
			continue;
		}

		childNode->ConditionalPostLoad();
		PreLoadNodes(childNode, Delegate);
	}

	USoundNodeWavePlayer* const wavePlayer = Cast<USoundNodeWavePlayer>(Node);
	if (!wavePlayer)
	{
		return;
	}

	USoundWave* const soundWave = wavePlayer->GetSoundWave();
	if (!soundWave)
	{
		return;
	}

	if (ForceRetainOnLoad) 
	{
		soundWave->OverrideLoadingBehavior(ESoundWaveLoadingBehavior::RetainOnLoad);
	}
	
	UAudioMixerBlueprintLibrary::PrimeSoundForPlayback(soundWave, Delegate);
}

void USoundCueList::PreLoadSoundList()
{
	FOnSoundLoadComplete onSoundLoadedDelegate;
	onSoundLoadedDelegate.BindDynamic(this, &USoundCueList::OnSoundLoaded);

	for (USoundCue* const& soundCue : SoundList)
	{
		if (!soundCue)
		{
			continue;
		}

		if (soundCue->FirstNode) 
		{
			PreLoadNodes(soundCue->FirstNode, onSoundLoadedDelegate);
		}
	}
}

void USoundCueList::ReleaseSoundList()
{
	for (USoundCue* const& soundCue : SoundList)
	{
		if (soundCue)
		{
			soundCue->ReleaseRetainedAudio();
		}
	}
}

void USoundCueList::OnSoundLoaded(const USoundWave* LoadedSoundWave, const bool WasCancelled)
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