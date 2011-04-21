##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=plugin
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/psc/11h11/code/kiku"
ProjectPath            := "/home/psc/11h11/code/kiku/plugin"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=psc
Date                   :=11-04-06
CodeLitePath           :="/home/psc/.codelite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=gcc
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
C_CmpOptions           := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/adin_pulseaudiolibpd$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/adin_pulseaudiolibpd$(ObjectSuffix): adin_pulseaudiolibpd.c $(IntermediateDirectory)/adin_pulseaudiolibpd$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/plugin/adin_pulseaudiolibpd.c" $(C_CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/adin_pulseaudiolibpd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/adin_pulseaudiolibpd$(DependSuffix): adin_pulseaudiolibpd.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/adin_pulseaudiolibpd$(ObjectSuffix) -MF$(IntermediateDirectory)/adin_pulseaudiolibpd$(DependSuffix) -MM "/home/psc/11h11/code/kiku/plugin/adin_pulseaudiolibpd.c"

$(IntermediateDirectory)/adin_pulseaudiolibpd$(PreprocessSuffix): adin_pulseaudiolibpd.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/adin_pulseaudiolibpd$(PreprocessSuffix) "/home/psc/11h11/code/kiku/plugin/adin_pulseaudiolibpd.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/adin_pulseaudiolibpd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/adin_pulseaudiolibpd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/adin_pulseaudiolibpd$(PreprocessSuffix)
	$(RM) $(OutputFile)


