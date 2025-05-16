// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BossArena : ModuleRules
{
	public BossArena(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AnimGraphRuntime", "AnimGraphRuntime"  });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayTags", 
			"GameplayAbilities", 
			"GameplayAbilities",
			"GameplayTasks", 
			"AIModule",
			"MotionWarping",
			"NavigationSystem",
			"Niagara"
		});
		PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
