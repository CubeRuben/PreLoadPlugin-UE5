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
	TArray<TObjectPtr<class USoundListBase>> SoundLists;

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
