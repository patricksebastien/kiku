##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=pamonitor
ConfigurationName      :=Release
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/psc/11h11/code/kiku"
ProjectPath            := "/home/psc/11h11/code/kiku/plugin/pulseaudiomon"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=psc
Date                   :=11-06-03
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
ObjectsFileList        :="/home/psc/11h11/code/kiku/plugin/pulseaudiomon/pamonitor.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             :=  $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  -O2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
RcIncludePath          :=
Libs                   :=
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/adin_pulseaudiolibpdmon$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/adin_pulseaudiolibpdmon$(ObjectSuffix): adin_pulseaudiolibpdmon.c $(IntermediateDirectory)/adin_pulseaudiolibpdmon$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/plugin/pulseaudiomon/adin_pulseaudiolibpdmon.c" $(C_CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/adin_pulseaudiolibpdmon$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/adin_pulseaudiolibpdmon$(DependSuffix): adin_pulseaudiolibpdmon.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/adin_pulseaudiolibpdmon$(ObjectSuffix) -MF$(IntermediateDirectory)/adin_pulseaudiolibpdmon$(DependSuffix) -MM "/home/psc/11h11/code/kiku/plugin/pulseaudiomon/adin_pulseaudiolibpdmon.c"

$(IntermediateDirectory)/adin_pulseaudiolibpdmon$(PreprocessSuffix): adin_pulseaudiolibpdmon.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/adin_pulseaudiolibpdmon$(PreprocessSuffix) "/home/psc/11h11/code/kiku/plugin/pulseaudiomon/adin_pulseaudiolibpdmon.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/adin_pulseaudiolibpdmon$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/adin_pulseaudiolibpdmon$(DependSuffix)
	$(RM) $(IntermediateDirectory)/adin_pulseaudiolibpdmon$(PreprocessSuffix)
	$(RM) $(OutputFile)


