// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DunegonEscape : ModuleRules
{
	public DunegonEscape(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
            "HTTP",
			"Json",
			"JsonUtilities",
			"EngineSettings"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"DunegonEscape",
			"DunegonEscape/Variant_Horror",
			"DunegonEscape/Variant_Horror/UI",
			"DunegonEscape/Variant_Shooter",
			"DunegonEscape/Variant_Shooter/AI",
			"DunegonEscape/Variant_Shooter/UI",
			"DunegonEscape/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
