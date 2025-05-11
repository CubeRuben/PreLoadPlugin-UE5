#pragma once

#include "CoreMinimal.h"
#include "SoundListBase.h"
#include "SoundWaveList.generated.h"

UCLASS(BlueprintType)
class AUDIOPRELOAD_API USoundWaveList : public USoundListBase
{
	GENERATED_BODY()

public:

	USoundWaveList();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class USoundWave*> SoundList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ForceRetainOnLoad;

	UFUNCTION()
	void OnSoundLoaded(const class USoundWave* LoadedSoundWave, const bool WasCancelled);

public:

	const TArray<class USoundWave*>& GetSoundList() const { return SoundList; }

	void PreLoadSoundList() override;
	void ReleaseSoundList() override;
};
