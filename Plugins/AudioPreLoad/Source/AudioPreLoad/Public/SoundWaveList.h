#pragma once

#include "CoreMinimal.h"
#include "SoundListBase.h"
#include "SoundWaveList.generated.h"

/**
 * ����� ��� ������ ������ ���� USoundWave
 */
UCLASS(BlueprintType)
class AUDIOPRELOAD_API USoundWaveList : public USoundListBase
{
	GENERATED_BODY()

public:

	/** ����������� ������ */
	USoundWaveList();

protected:
	
	/** ������ ������� USoundWave */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class USoundWave*> SoundList;

	/** ������ �� ������������� ��������� �������� ������� ������ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ForceRetainOnLoad;

	/** �����-�������� ����� (callback) ��� �������� ����� � ��� */
	UFUNCTION()
	void OnSoundLoaded(const class USoundWave* LoadedSoundWave, const bool WasCancelled);

public:

	/** ������ ������ �� ������ ������ */
	const TArray<class USoundWave*>& GetSoundList() const { return SoundList; }

	/** ��������������� ������� �� USoundListBase */
	void PreLoadSoundList() override;
	void ReleaseSoundList() override;
};
