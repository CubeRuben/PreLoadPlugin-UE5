#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AudioPreLoadLog.h"
#include "AudioList.generated.h"

UCLASS(BlueprintType)
class AUDIOPRELOAD_API UAudioList : public UDataAsset
{
	GENERATED_BODY()

public:

    UAudioList();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USoundWave*> SoundList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ForceRetainOnLoad;

	UFUNCTION()
	void OnSoundLoaded(const USoundWave* LoadedSoundWave, const bool WasCancelled);

public:

	const TArray<USoundWave*>& GetSoundList() const { return SoundList; }

	UFUNCTION(BlueprintCallable)
	void PreLoadSoundList();

};
