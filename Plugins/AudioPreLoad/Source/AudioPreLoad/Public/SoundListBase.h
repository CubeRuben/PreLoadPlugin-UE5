#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SoundListBase.generated.h"

UCLASS(BlueprintType, Abstract)
class AUDIOPRELOAD_API USoundListBase : public UDataAsset
{
	GENERATED_BODY()

public:

	USoundListBase();

	UFUNCTION(BlueprintCallable)
	virtual void PreLoadSoundList() {}

	UFUNCTION(BlueprintCallable)
	virtual void ReleaseSoundList() {}
};
