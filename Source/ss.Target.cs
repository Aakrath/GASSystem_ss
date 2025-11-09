// Copyright SS Mechanics

using UnrealBuildTool;
using System.Collections.Generic;

public class ssTarget : TargetRules
{
	public ssTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ss" } );
	}
}
