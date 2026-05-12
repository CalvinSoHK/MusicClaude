using UnrealBuildTool;

public class MusicClaudeTarget : TargetRules
{
    public MusicClaudeTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("MusicClaude");
    }
}
