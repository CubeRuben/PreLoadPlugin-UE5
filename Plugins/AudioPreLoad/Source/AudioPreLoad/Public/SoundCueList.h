#pragma once

#include "CoreMinimal.h"
#include "SoundListBase.h"
#include "SoundCueList.generated.h"

/**
 * ����� ��� ������ ������ ���� USoundCue
 */
UCLASS(BlueprintType)
class AUDIOPRELOAD_API USoundCueList : public USoundListBase
{
	GENERATED_BODY()

public:

	/** ����������� ������ */
	USoundCueList();

protected:

	/** ������ ������� USoundCue */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class USoundCue*> SoundList;

	/** ������ �� ������������� ��������� �������� ������� ������ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ForceRetainOnLoad;

	/** ����� ��� ������������ �������� �� ����� � USoundCue */
	void PreLoadNodes(USoundNode* Node, const class FOnSoundLoadComplete& Delegate);

	/** �����-�������� ����� (callback) ��� �������� ����� � ��� */
	UFUNCTION()
	void OnSoundLoaded(const class USoundWave* LoadedSoundWave, const bool WasCancelled);

public:

	/** ������ ������ �� ������ ������ */
	const TArray<class USoundCue*>& GetSoundList() const { return SoundList; }

	/** ��������������� ������� �� USoundListBase */
	void PreLoadSoundList() override;
	void ReleaseSoundList() override;
};
