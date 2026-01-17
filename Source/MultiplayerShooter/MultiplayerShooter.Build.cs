// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MultiplayerShooter : ModuleRules
{
	public MultiplayerShooter(ReadOnlyTargetRules Target) : base(Target)
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
			"OnlineSubsystemSteam",
			"OnlineSubsystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MultiplayerShooter",
			"MultiplayerShooter/Variant_Platforming",
			"MultiplayerShooter/Variant_Platforming/Animation",
			"MultiplayerShooter/Variant_Combat",
			"MultiplayerShooter/Variant_Combat/AI",
			"MultiplayerShooter/Variant_Combat/Animation",
			"MultiplayerShooter/Variant_Combat/Gameplay",
			"MultiplayerShooter/Variant_Combat/Interfaces",
			"MultiplayerShooter/Variant_Combat/UI",
			"MultiplayerShooter/Variant_SideScrolling",
			"MultiplayerShooter/Variant_SideScrolling/AI",
			"MultiplayerShooter/Variant_SideScrolling/Gameplay",
			"MultiplayerShooter/Variant_SideScrolling/Interfaces",
			"MultiplayerShooter/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
