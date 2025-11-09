// Copyright SS Mechanics

using UnrealBuildTool;
using System.Collections.Generic;

public class ssEditorTarget : TargetRules
{
	public ssEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ss" } );
	}
}
