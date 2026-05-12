using UnrealBuildTool;

public class MusicClaudeEditorTarget : TargetRules
{
    public MusicClaudeEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("MusicClaude");
    }
}
