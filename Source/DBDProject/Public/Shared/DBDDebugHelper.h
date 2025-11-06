#pragma once
#include "GameplayTagContainer.h"

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
			const FString FinalMsg = NetRoleTitle + TEXT(": ") + UEnum::GetValueAsString(NetRoleToPrint) +
				TEXT(" PlayerId: ") + FString::FromInt(PlayerId);
			GEngine->AddOnScreenDebugMessage(Inkey, 7.0f, Color, FinalMsg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}

	template <typename FmtType, typename... Args>
	static void Print(int32 Inkey, const FmtType& Format, Args... FormatArgs)
	{
		FString FinalMsg = FString::Printf(Format, FormatArgs...);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(Inkey, 7.0f, FColor::MakeRandomColor(), FinalMsg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
	
	static void DebugStringWithNetMode(const UObject* WorldContextObject, FString DebugString, FVector Location, float Duration = -1.f)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
		FString Prefix;
		if (World)
		{
			if (World->WorldType == EWorldType::PIE)
			{
				switch (World->GetNetMode())
				{
				case NM_Client:
					// GPlayInEditorID 0 is always the server, so 1 will be first client.
					// You want to keep this logic in sync with GeneratePIEViewportWindowTitle and UpdatePlayInEditorWorldDebugString
					//Prefix = FString::Printf(TEXT("Client %d: "), GPlayInEditorID);
					//Prefix = FString::Printf(TEXT("Client %d: "), UE::GetPlayInEditorID());
					break;
				case NM_DedicatedServer:
				case NM_ListenServer:
					Prefix = FString::Printf(TEXT("Server: "));
					break;
				case NM_Standalone:
					break;
				}
			}
		}
		FString FinalMsg = Prefix + DebugString;
		DrawDebugString(World, Location, FinalMsg,0,FColor::White,Duration);
	}
}
