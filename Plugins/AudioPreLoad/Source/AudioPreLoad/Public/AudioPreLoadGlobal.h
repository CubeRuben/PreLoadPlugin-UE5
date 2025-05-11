#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioList.h"
#include "AudioPreLoadGlobal.generated.h"

UCLASS(BlueprintType)
class AUDIOPRELOAD_API AAudioPreLoadGlobal : public AActor
{
	GENERATED_BODY()
	
public:	

	AAudioPreLoadGlobal();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UAudioList> AudioList;

	virtual void BeginPlay() override;

};
