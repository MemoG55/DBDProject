#pragma once

namespace Debug
{
	static void Print(const FString& Msg, int32 Inkey, const FColor& Color = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(Inkey, 7.0f, Color, Msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}

	static void Print(const FString& FloatTitle, float FloatValueToPrint, int32 Inkey,
		const FColor& Color = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			const FString FinalMsg = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValueToPrint);
			GEngine->AddOnScreenDebugMessage(Inkey, 7.0f, Color, FinalMsg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
	static void Print(const FString& NetRoleTitle, ENetRole NetRoleToPrint, int32 Inkey,
		const FColor& Color = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			const FString FinalMsg = NetRoleTitle + TEXT(": ") + UEnum::GetValueAsString(NetRoleToPrint);
			GEngine->AddOnScreenDebugMessage(Inkey, 7.0f, Color, FinalMsg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
	static void Print(const FString& NetRoleTitle, ENetRole NetRoleToPrint, int32 PlayerId, int32 Inkey,
		const FColor& Color = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			const FString FinalMsg = NetRoleTitle + TEXT(": ") + UEnum::GetValueAsString(NetRoleToPrint) + TEXT(" PlayerId: ") + FString::FromInt(PlayerId);
			GEngine->AddOnScreenDebugMessage(Inkey, 7.0f, Color, FinalMsg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
}