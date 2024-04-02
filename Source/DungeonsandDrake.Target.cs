

using UnrealBuildTool;
using System.Collections.Generic;

public class DungeonsandDrakeTarget : TargetRules
{
	public DungeonsandDrakeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "DungeonsandDrake" } );
	}
}
