#include "AudioPreLoadTrigger.h"

#include "AudioList.h"

#include <Components/BoxComponent.h>

AAudioPreLoadTrigger::AAudioPreLoadTrigger()
{
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	TriggerComponent->SetCollisionProfileName("OverlapAll");
	RootComponent = TriggerComponent;
}

void AAudioPreLoadTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerComponent) 
	{
		TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AAudioPreLoadTrigger::OnOverlapBegin);
	}
}

void AAudioPreLoadTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerController* const controller = GetWorld()->GetFirstPlayerController();
	
	if (!controller)
	{
		return;
	}

	APawn* const pawn = controller->GetPawn();

	if (!pawn)
	{
		return;
	}

	if (pawn == OtherActor)
	{
		if (AudioList)
		{
			AudioList->PreLoadSoundList();
		}
	}
}


