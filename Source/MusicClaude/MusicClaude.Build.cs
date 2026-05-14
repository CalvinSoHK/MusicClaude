using UnrealBuildTool;

public class MusicClaude : ModuleRules
{
    public MusicClaude(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG",
            "AudioMixer",
            "SlateCore",
            "Slate"
        });
    }
}
