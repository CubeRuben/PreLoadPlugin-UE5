#include "AudioPreLoadGlobal.h"

#include "SoundListBase.h"

AAudioPreLoadGlobal::AAudioPreLoadGlobal() :
	SoundLists()
{ }

void AAudioPreLoadGlobal::BeginPlay()
{
	Super::BeginPlay();
	
	// �������� ����� ������� ������� ������
	for (USoundListBase* const & soundList : SoundLists) 
	{
		// �������� ��������� �� nullptr
		if (soundList)
		{
			// �������� ������ � ���
			soundList->PreLoadSoundList();
		}
	}
}

void AAudioPreLoadGlobal::BeginDestroy()
{
	Super::BeginDestroy();

	// �������� ����� ������� ������� ������
	for (USoundListBase* const& soundList : SoundLists)
	{
		// �������� ��������� �� nullptr
		if (soundList)
		{
			// "������������" ������ �� ����
			soundList->ReleaseSoundList();
		}
	}
}

