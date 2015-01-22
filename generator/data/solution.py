[[[cog
from __main__ import guid, projects

if version == "12":
    cog.outl()
cog.outl("Microsoft Visual Studio Solution File, Format Version 12.00")
cog.outl("# Visual Studio 20" + version)
if version == "12":
    pass
elif version == "13":
    cog.outl("VisualStudioVersion = 12.0.30501.0")
    cog.outl("MinimumVisualStudioVersion = 10.0.40219.1")
else:
    cog.error("Unsupported Visual Studio version: %r" % version)

prefix = 'Project("{%s}") = ' % guid
for p in projects:
    cog.out(prefix)
    cog.outl('"{name}", "{name}\{name}.vcxproj", "{{{guid}}}"'.format_map(p))
    cog.outl('EndProject')
]]]
[[[end]]]
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|Win32 = Debug|Win32
		Release|Win32 = Release|Win32
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
        [[[cog
        for p in projects:
            cog.outl("{{{guid}}}.Debug|Win32.ActiveCfg = Debug|Win32".format_map(p))
            cog.outl("{{{guid}}}.Debug|Win32.Build.0 = Debug|Win32".format_map(p))
            cog.outl("{{{guid}}}.Release|Win32.ActiveCfg = Release|Win32".format_map(p))
            cog.outl("{{{guid}}}.Release|Win32.Build.0 = Release|Win32".format_map(p))
        ]]]
        [[[end]]]
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
EndGlobal
