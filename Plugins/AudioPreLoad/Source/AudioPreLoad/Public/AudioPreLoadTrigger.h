#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioPreLoadTrigger.generated.h"

UCLASS()
class AUDIOPRELOAD_API AAudioPreLoadTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

	AAudioPreLoadTrigger();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* TriggerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UAudioList> AudioList;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
