// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PRO135_Proj1_NHemez : ModuleRules
{
	public PRO135_Proj1_NHemez(ReadOnlyTargetRules Target) : base(Target)
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
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"PRO135_Proj1_NHemez",
			"PRO135_Proj1_NHemez/Variant_Platforming",
			"PRO135_Proj1_NHemez/Variant_Platforming/Animation",
			"PRO135_Proj1_NHemez/Variant_Combat",
			"PRO135_Proj1_NHemez/Variant_Combat/AI",
			"PRO135_Proj1_NHemez/Variant_Combat/Animation",
			"PRO135_Proj1_NHemez/Variant_Combat/Gameplay",
			"PRO135_Proj1_NHemez/Variant_Combat/Interfaces",
			"PRO135_Proj1_NHemez/Variant_Combat/UI",
			"PRO135_Proj1_NHemez/Variant_SideScrolling",
			"PRO135_Proj1_NHemez/Variant_SideScrolling/AI",
			"PRO135_Proj1_NHemez/Variant_SideScrolling/Gameplay",
			"PRO135_Proj1_NHemez/Variant_SideScrolling/Interfaces",
			"PRO135_Proj1_NHemez/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
