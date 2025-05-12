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
	// �������� ����� ������� �������� �����
	for (USoundNode* childNode : Node->ChildNodes)
	{
		// �������� ��������� �� nullptr
		if (!childNode)
		{
			// ������� �� ��������� ��� �����
			continue;
		}

		childNode->ConditionalPostLoad();
		// ����������� ����� 
		PreLoadNodes(childNode, Delegate);
	}

	// ���� ���� � USoundNodeWavePlayer
	USoundNodeWavePlayer* const wavePlayer = Cast<USoundNodeWavePlayer>(Node);
	// �������� ��������� �� nullptr
	if (!wavePlayer)
	{
		return;
	}

	// ��������� USoundWave �� USoundNodeWavePlayer
	USoundWave* const soundWave = wavePlayer->GetSoundWave();
	// �������� ��������� �� nullptr
	if (!soundWave)
	{
		return;
	}

	// �������� ������������� ��������������� ��������� �������� ������
	if (ForceRetainOnLoad) 
	{
		// ��������������� ��������� �������� ������
		soundWave->OverrideLoadingBehavior(ESoundWaveLoadingBehavior::RetainOnLoad);
	}
	
	// �������� ����� � ���
	UAudioMixerBlueprintLibrary::PrimeSoundForPlayback(soundWave, Delegate);
}

void USoundCueList::PreLoadSoundList()
{
	// �������� �������� ��� ��������� ������
	FOnSoundLoadComplete onSoundLoadedDelegate;
	// �������� ������
	onSoundLoadedDelegate.BindDynamic(this, &USoundCueList::OnSoundLoaded);

	// �������� ����� ������� ������
	for (USoundCue* const& soundCue : SoundList)
	{
		// �������� ��������� �� nullptr
		if (!soundCue)
		{
			// ������� �� ��������� ��� �����
			continue;
		}

		// �������� ��������� FirstNode �� nullptr
		if (soundCue->FirstNode) 
		{
			// ������ ������ ������ � SoundCue
			PreLoadNodes(soundCue->FirstNode, onSoundLoadedDelegate);
		}
	}
}

void USoundCueList::ReleaseSoundList()
{
	// �������� ����� ������� ������
	for (USoundCue* const& soundCue : SoundList)
	{
		// �������� ��������� �� nullptr
		if (soundCue)
		{
			// "������������" ����� ��� �������� �������� �� ����
			soundCue->ReleaseRetainedAudio();
		}
	}
}

void USoundCueList::OnSoundLoaded(const USoundWave* LoadedSoundWave, const bool WasCancelled)
{
	// �������� ��������� �� nullptr
	if (!LoadedSoundWave)
		return;

	// ��������� �������� ������ �����
	FString soundName;
	LoadedSoundWave->GetName(soundName);

	if (WasCancelled)
	{
		// ����� � �������, ���� �������� ������
		UE_LOG(LogAudioPreLoad, Log, TEXT("An error occurred during preload of: %s"), *soundName);
	}
	else
	{
		// ����� � �������, ���� �������� ���� ��������
		UE_LOG(LogAudioPreLoad, Log, TEXT("Successfully preloaded: %s"), *soundName);
	}
}