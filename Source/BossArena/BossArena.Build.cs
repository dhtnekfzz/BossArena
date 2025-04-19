// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BossArena : ModuleRules
{
	public BossArena(ReadOnlyTargetRules Target) : base(Target)
	{
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
		});
		PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
