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
	// �������� �������� ��� ��������� ������
	FOnSoundLoadComplete onSoundLoadedDelegate;
	// �������� ������
	onSoundLoadedDelegate.BindDynamic(this, &USoundWaveList::OnSoundLoaded);

	// �������� ����� ������� ������
	for (USoundWave* const& soundWave : SoundList)
	{
		// �������� ��������� �� nullptr
		if (!soundWave)
		{
			// ������� �� ��������� ��� �����
			continue;
		}

		// �������� ������������� ��������������� ��������� �������� ������
		if (ForceRetainOnLoad)
		{
			// ��������������� ��������� �������� ������
			soundWave->OverrideLoadingBehavior(ESoundWaveLoadingBehavior::RetainOnLoad);
		}

		// �������� ����� � ���
		UAudioMixerBlueprintLibrary::PrimeSoundForPlayback(soundWave, onSoundLoadedDelegate);
	}
}

void USoundWaveList::ReleaseSoundList()
{
	// �������� ����� ������� ������
	for (USoundWave* const& soundWave : SoundList)
	{
		// �������� ��������� �� nullptr
		if (soundWave)
		{
			// "������������" ����� ��� �������� �������� �� ����
			soundWave->ReleaseCompressedAudio();
		}
	}
}

void USoundWaveList::OnSoundLoaded(const USoundWave* LoadedSoundWave, const bool WasCancelled)
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