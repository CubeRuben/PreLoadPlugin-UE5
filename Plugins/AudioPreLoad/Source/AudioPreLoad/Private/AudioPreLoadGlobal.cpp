#include "AudioPreLoadGlobal.h"

#include "AudioList.h"

AAudioPreLoadGlobal::AAudioPreLoadGlobal() :
	AudioList(nullptr)
{ }

void AAudioPreLoadGlobal::BeginPlay()
{
	Super::BeginPlay();
	
	if (AudioList) 
	{
		AudioList->PreLoadSoundList();
	}
}

