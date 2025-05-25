#pragma once

UENUM(BlueprintType)
enum class EFramerate : uint8
{
	FPS_30 UMETA(DisplayName="30 FPS"),
	FPS_60 UMETA(DisplayName="60 FPS"),
	FPS_120 UMETA(DisplayName="120 FPS"),
	FPS_Uncapped UMETA(DisplayName="Uncapped FPS"),
};

class FFramerateUtils
{
public:
	static int EnumToValue(const EFramerate& InFrameRate)
	{
		switch (InFrameRate)
		{
		case EFramerate::FPS_30: return 30;
		case EFramerate::FPS_60: return 60;
		case EFramerate::FPS_120: return 120;
		default: return 0;
		}
	}

	static FString EnumToString(EFramerate InFrameRate)
	{
		const auto Value=EnumToValue(InFrameRate);
		return Value>0 ? FString::Printf(TEXT("%d FPS"), Value) : TEXT("Uncapped FPS");
	}
};