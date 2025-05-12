#include "AudioPreLoadTrigger.h"

#include "SoundListBase.h"

#include <Components/BoxComponent.h>

AAudioPreLoadTrigger::AAudioPreLoadTrigger()
{
	// Создание компонента коробки
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	// Найстркойка компонента как триггра
	TriggerComponent->SetCollisionProfileName("OverlapAll");
	// Назначение компонента как главного компонента
	RootComponent = TriggerComponent;
}

void AAudioPreLoadTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	// Проверка указателя на nullptr
	if (TriggerComponent) 
	{
		// Привязка делегатов к триггеру
		TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AAudioPreLoadTrigger::OnOverlapBegin);
		TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &AAudioPreLoadTrigger::OnOverlapEnd);
	}
}

void AAudioPreLoadTrigger::BeginDestroy()
{
	Super::BeginDestroy();

	// Итерация всего массива списков звуков
	for (USoundListBase* const& soundList : SoundLists)
	{
		// Проверка указателя на nullptr
		if (soundList)
		{
			// "Освобождение" звуков из кэша
			soundList->ReleaseSoundList();
		}
	}
}

void AAudioPreLoadTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Запрос контроллера игрока
	APlayerController* const controller = GetWorld()->GetFirstPlayerController();
	// Проверка указателя на nullptr
	if (!controller)
	{
		return;
	}

	// Запрос пешки игрока у контроллера
	APawn* const pawn = controller->GetPawn();
	// Проверка указателя на nullptr
	if (!pawn)
	{
		return;
	}

	// Проверка, что актор и пешка игрока - один и тот же объект
	if (pawn == OtherActor)
	{
		// Итерация всего массива списков звуков
		for (USoundListBase* const& soundList : SoundLists)
		{
			// Проверка указателя на nullptr
			if (soundList)
			{
				// "Освобождение" звуков из кэша
				soundList->PreLoadSoundList();
			}
		}
	}
}

void AAudioPreLoadTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Запрос контроллера игрока
	APlayerController* const controller = GetWorld()->GetFirstPlayerController();
	// Проверка указателя на nullptr
	if (!controller)
	{
		return;
	}

	// Запрос пешки игрока у контроллера
	APawn* const pawn = controller->GetPawn();
	// Проверка указателя на nullptr
	if (!pawn)
	{
		return;
	}

	// Проверка, что актор и пешка игрока - один и тот же объект
	if (pawn == OtherActor)
	{
		// Итерация всего массива списков звуков
		for (USoundListBase* const& soundList : SoundLists)
		{
			// Проверка указателя на nullptr
			if (soundList)
			{
				// "Освобождение" звуков из кэша
				soundList->ReleaseSoundList();
			}
		}
	}
}


