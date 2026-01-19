// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MultiplayerSessions : ModuleRules
{
	public MultiplayerSessions(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange([]);


		PrivateIncludePaths.AddRange([]);


		PublicDependencyModuleNames.AddRange(
			[
				"Core",
				"OnlineSubsystem",
				"OnlineSubsystemSteam",
				"UMG",
				"Slate",
				"SlateCore"
		]);


		PrivateDependencyModuleNames.AddRange(
			[
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
			]
		);


		DynamicallyLoadedModuleNames.AddRange(
			[
			]
		);
	}
}