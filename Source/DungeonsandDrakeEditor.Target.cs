

using UnrealBuildTool;
using System.Collections.Generic;

public class DungeonsandDrakeEditorTarget : TargetRules
{
	public DungeonsandDrakeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "DungeonsandDrake" } );
	}
}
