// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DBDProject : ModuleRules
{
	public DBDProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"AdvancedSessions",
			"GameplayTags", "GameplayAbilities", "GameplayTasks", "UMG", "SkeletalMerging", "NetCore",
			"AssetRegistry"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "CommonUI", "MotionWarping" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });


		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}