#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioPreLoadGlobal.generated.h"

UCLASS(BlueprintType)
class AUDIOPRELOAD_API AAudioPreLoadGlobal : public AActor
{
	GENERATED_BODY()
	
public:	

	AAudioPreLoadGlobal();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<class USoundListBase>> SoundLists;

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
