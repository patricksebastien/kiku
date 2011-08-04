##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=kiku
ConfigurationName      :=Release
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/psc/11h11/code/kiku"
ProjectPath            := "/home/psc/11h11/code/kiku/kiku"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=psc
Date                   :=11-08-04
CodeLitePath           :="/home/psc/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/psc/11h11/code/kiku/kiku/kiku.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -O2 $(shell /home/psc/src/wx291svnrelease/bin/wx-config --cxxflags) $(shell /home/psc/src/juliuscvs/bin/libjulius-config --cflags) $(shell /home/psc/src/juliuscvs/bin/libsent-config --cflags) $(shell /usr/bin/xosd-config --cflags) $(shell pkg-config --cflags libnotify) $(shell pkg-config gconf-2.0 --cflags) $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  -s $(shell /home/psc/src/wx291svnrelease/bin/wx-config --libs) $(shell /home/psc/src/juliuscvs/bin/libjulius-config --libs) $(shell /home/psc/src/juliuscvs/bin/libsent-config --libs) $(shell /usr/bin/xosd-config --libs) $(shell pkg-config --libs libnotify) $(shell pkg-config gconf-2.0 --libs) -Wl,-export-dynamic -Wl,-whole-archive ../common/libpd.a -Wl,-no-whole-archive
IncludePath            :=  $(IncludeSwitch). 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)lo $(LibrarySwitch)xdo $(LibrarySwitch)Xtst 
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/gui$(ObjectSuffix) $(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/julius$(ObjectSuffix) $(IntermediateDirectory)/jsonreader$(ObjectSuffix) $(IntermediateDirectory)/jsonval$(ObjectSuffix) $(IntermediateDirectory)/jsonwriter$(ObjectSuffix) $(IntermediateDirectory)/language$(ObjectSuffix) $(IntermediateDirectory)/gui_v2capplication$(ObjectSuffix) $(IntermediateDirectory)/v2capplication$(ObjectSuffix) $(IntermediateDirectory)/gui_v2ceditor$(ObjectSuffix) \
	$(IntermediateDirectory)/v2ceditor$(ObjectSuffix) $(IntermediateDirectory)/gui_activeword$(ObjectSuffix) $(IntermediateDirectory)/activeword$(ObjectSuffix) $(IntermediateDirectory)/web$(ObjectSuffix) 

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
$(IntermediateDirectory)/gui$(ObjectSuffix): gui.cpp $(IntermediateDirectory)/gui$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/gui.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gui$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui$(DependSuffix): gui.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui$(ObjectSuffix) -MF$(IntermediateDirectory)/gui$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/gui.cpp"

$(IntermediateDirectory)/gui$(PreprocessSuffix): gui.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/gui.cpp"

$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/main.cpp"

$(IntermediateDirectory)/julius$(ObjectSuffix): julius.cpp $(IntermediateDirectory)/julius$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/julius.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/julius$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/julius$(DependSuffix): julius.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/julius$(ObjectSuffix) -MF$(IntermediateDirectory)/julius$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/julius.cpp"

$(IntermediateDirectory)/julius$(PreprocessSuffix): julius.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/julius$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/julius.cpp"

$(IntermediateDirectory)/jsonreader$(ObjectSuffix): jsonreader.cpp $(IntermediateDirectory)/jsonreader$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/jsonreader.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/jsonreader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jsonreader$(DependSuffix): jsonreader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jsonreader$(ObjectSuffix) -MF$(IntermediateDirectory)/jsonreader$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/jsonreader.cpp"

$(IntermediateDirectory)/jsonreader$(PreprocessSuffix): jsonreader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jsonreader$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/jsonreader.cpp"

$(IntermediateDirectory)/jsonval$(ObjectSuffix): jsonval.cpp $(IntermediateDirectory)/jsonval$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/jsonval.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/jsonval$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jsonval$(DependSuffix): jsonval.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jsonval$(ObjectSuffix) -MF$(IntermediateDirectory)/jsonval$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/jsonval.cpp"

$(IntermediateDirectory)/jsonval$(PreprocessSuffix): jsonval.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jsonval$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/jsonval.cpp"

$(IntermediateDirectory)/jsonwriter$(ObjectSuffix): jsonwriter.cpp $(IntermediateDirectory)/jsonwriter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/jsonwriter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/jsonwriter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jsonwriter$(DependSuffix): jsonwriter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jsonwriter$(ObjectSuffix) -MF$(IntermediateDirectory)/jsonwriter$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/jsonwriter.cpp"

$(IntermediateDirectory)/jsonwriter$(PreprocessSuffix): jsonwriter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jsonwriter$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/jsonwriter.cpp"

$(IntermediateDirectory)/language$(ObjectSuffix): language.cpp $(IntermediateDirectory)/language$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/language.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/language$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/language$(DependSuffix): language.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/language$(ObjectSuffix) -MF$(IntermediateDirectory)/language$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/language.cpp"

$(IntermediateDirectory)/language$(PreprocessSuffix): language.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/language$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/language.cpp"

$(IntermediateDirectory)/gui_v2capplication$(ObjectSuffix): gui_v2capplication.cpp $(IntermediateDirectory)/gui_v2capplication$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/gui_v2capplication.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gui_v2capplication$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui_v2capplication$(DependSuffix): gui_v2capplication.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui_v2capplication$(ObjectSuffix) -MF$(IntermediateDirectory)/gui_v2capplication$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/gui_v2capplication.cpp"

$(IntermediateDirectory)/gui_v2capplication$(PreprocessSuffix): gui_v2capplication.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui_v2capplication$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/gui_v2capplication.cpp"

$(IntermediateDirectory)/v2capplication$(ObjectSuffix): v2capplication.cpp $(IntermediateDirectory)/v2capplication$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/v2capplication.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/v2capplication$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/v2capplication$(DependSuffix): v2capplication.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/v2capplication$(ObjectSuffix) -MF$(IntermediateDirectory)/v2capplication$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/v2capplication.cpp"

$(IntermediateDirectory)/v2capplication$(PreprocessSuffix): v2capplication.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/v2capplication$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/v2capplication.cpp"

$(IntermediateDirectory)/gui_v2ceditor$(ObjectSuffix): gui_v2ceditor.cpp $(IntermediateDirectory)/gui_v2ceditor$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/gui_v2ceditor.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gui_v2ceditor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui_v2ceditor$(DependSuffix): gui_v2ceditor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui_v2ceditor$(ObjectSuffix) -MF$(IntermediateDirectory)/gui_v2ceditor$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/gui_v2ceditor.cpp"

$(IntermediateDirectory)/gui_v2ceditor$(PreprocessSuffix): gui_v2ceditor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui_v2ceditor$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/gui_v2ceditor.cpp"

$(IntermediateDirectory)/v2ceditor$(ObjectSuffix): v2ceditor.cpp $(IntermediateDirectory)/v2ceditor$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/v2ceditor.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/v2ceditor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/v2ceditor$(DependSuffix): v2ceditor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/v2ceditor$(ObjectSuffix) -MF$(IntermediateDirectory)/v2ceditor$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/v2ceditor.cpp"

$(IntermediateDirectory)/v2ceditor$(PreprocessSuffix): v2ceditor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/v2ceditor$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/v2ceditor.cpp"

$(IntermediateDirectory)/gui_activeword$(ObjectSuffix): gui_activeword.cpp $(IntermediateDirectory)/gui_activeword$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/gui_activeword.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gui_activeword$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui_activeword$(DependSuffix): gui_activeword.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui_activeword$(ObjectSuffix) -MF$(IntermediateDirectory)/gui_activeword$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/gui_activeword.cpp"

$(IntermediateDirectory)/gui_activeword$(PreprocessSuffix): gui_activeword.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui_activeword$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/gui_activeword.cpp"

$(IntermediateDirectory)/activeword$(ObjectSuffix): activeword.cpp $(IntermediateDirectory)/activeword$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/activeword.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/activeword$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/activeword$(DependSuffix): activeword.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/activeword$(ObjectSuffix) -MF$(IntermediateDirectory)/activeword$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/activeword.cpp"

$(IntermediateDirectory)/activeword$(PreprocessSuffix): activeword.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/activeword$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/activeword.cpp"

$(IntermediateDirectory)/web$(ObjectSuffix): web.cpp $(IntermediateDirectory)/web$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/psc/11h11/code/kiku/kiku/web.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/web$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/web$(DependSuffix): web.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/web$(ObjectSuffix) -MF$(IntermediateDirectory)/web$(DependSuffix) -MM "/home/psc/11h11/code/kiku/kiku/web.cpp"

$(IntermediateDirectory)/web$(PreprocessSuffix): web.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/web$(PreprocessSuffix) "/home/psc/11h11/code/kiku/kiku/web.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/gui$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gui$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gui$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/julius$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/julius$(DependSuffix)
	$(RM) $(IntermediateDirectory)/julius$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/jsonreader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/jsonreader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/jsonreader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/jsonval$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/jsonval$(DependSuffix)
	$(RM) $(IntermediateDirectory)/jsonval$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/jsonwriter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/jsonwriter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/jsonwriter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/language$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/language$(DependSuffix)
	$(RM) $(IntermediateDirectory)/language$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gui_v2capplication$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gui_v2capplication$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gui_v2capplication$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/v2capplication$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/v2capplication$(DependSuffix)
	$(RM) $(IntermediateDirectory)/v2capplication$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gui_v2ceditor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gui_v2ceditor$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gui_v2ceditor$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/v2ceditor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/v2ceditor$(DependSuffix)
	$(RM) $(IntermediateDirectory)/v2ceditor$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gui_activeword$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gui_activeword$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gui_activeword$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/activeword$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/activeword$(DependSuffix)
	$(RM) $(IntermediateDirectory)/activeword$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/web$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/web$(DependSuffix)
	$(RM) $(IntermediateDirectory)/web$(PreprocessSuffix)
	$(RM) $(OutputFile)


