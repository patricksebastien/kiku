##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=kiku
ConfigurationName      :=Release
WorkspacePath          := "/home/psc/src/kiku"
ProjectPath            := "/home/psc/src/kiku/kiku"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=psc
Date                   :=26/08/15
CodeLitePath           :="/home/psc/.codelite"
LinkerName             :=g++
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="kiku.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -s $(shell wx-config --libs) $(shell /home/psc/src/juliuscvs/bin/libjulius-config --libs) $(shell /home/psc/src/juliuscvs/bin/libsent-config --libs) $(shell /usr/bin/xosd-config --libs) $(shell pkg-config --libs libnotify) $(shell pkg-config gconf-2.0 --libs) -Wl,-export-dynamic -Wl,-whole-archive ../common/libpd.a -Wl,-no-whole-archive
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)lo $(LibrarySwitch)xdo $(LibrarySwitch)Xtst 
ArLibs                 :=  "liblo" "xdo.a" "Xtst" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -DLIBNOTIFYVER=4 $(shell wx-config --cppflags) $(shell /home/psc/src/juliuscvs/bin/libjulius-config --cflags) $(shell /home/psc/src/juliuscvs/bin/libsent-config --cflags) $(shell /usr/bin/xosd-config --cflags) $(shell pkg-config --cflags libnotify) $(shell pkg-config gconf-2.0 --cflags) $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/gui.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/julius.cpp$(ObjectSuffix) $(IntermediateDirectory)/jsonreader.cpp$(ObjectSuffix) $(IntermediateDirectory)/jsonval.cpp$(ObjectSuffix) $(IntermediateDirectory)/jsonwriter.cpp$(ObjectSuffix) $(IntermediateDirectory)/language.cpp$(ObjectSuffix) $(IntermediateDirectory)/gui_v2capplication.cpp$(ObjectSuffix) $(IntermediateDirectory)/v2capplication.cpp$(ObjectSuffix) $(IntermediateDirectory)/gui_v2ceditor.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/v2ceditor.cpp$(ObjectSuffix) $(IntermediateDirectory)/gui_activeword.cpp$(ObjectSuffix) $(IntermediateDirectory)/activeword.cpp$(ObjectSuffix) $(IntermediateDirectory)/web.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/gui.cpp$(ObjectSuffix): gui.cpp $(IntermediateDirectory)/gui.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/gui.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gui.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui.cpp$(DependSuffix): gui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gui.cpp$(DependSuffix) -MM "gui.cpp"

$(IntermediateDirectory)/gui.cpp$(PreprocessSuffix): gui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui.cpp$(PreprocessSuffix) "gui.cpp"

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/julius.cpp$(ObjectSuffix): julius.cpp $(IntermediateDirectory)/julius.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/julius.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/julius.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/julius.cpp$(DependSuffix): julius.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/julius.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/julius.cpp$(DependSuffix) -MM "julius.cpp"

$(IntermediateDirectory)/julius.cpp$(PreprocessSuffix): julius.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/julius.cpp$(PreprocessSuffix) "julius.cpp"

$(IntermediateDirectory)/jsonreader.cpp$(ObjectSuffix): jsonreader.cpp $(IntermediateDirectory)/jsonreader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/jsonreader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/jsonreader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jsonreader.cpp$(DependSuffix): jsonreader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jsonreader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/jsonreader.cpp$(DependSuffix) -MM "jsonreader.cpp"

$(IntermediateDirectory)/jsonreader.cpp$(PreprocessSuffix): jsonreader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jsonreader.cpp$(PreprocessSuffix) "jsonreader.cpp"

$(IntermediateDirectory)/jsonval.cpp$(ObjectSuffix): jsonval.cpp $(IntermediateDirectory)/jsonval.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/jsonval.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/jsonval.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jsonval.cpp$(DependSuffix): jsonval.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jsonval.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/jsonval.cpp$(DependSuffix) -MM "jsonval.cpp"

$(IntermediateDirectory)/jsonval.cpp$(PreprocessSuffix): jsonval.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jsonval.cpp$(PreprocessSuffix) "jsonval.cpp"

$(IntermediateDirectory)/jsonwriter.cpp$(ObjectSuffix): jsonwriter.cpp $(IntermediateDirectory)/jsonwriter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/jsonwriter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/jsonwriter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jsonwriter.cpp$(DependSuffix): jsonwriter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jsonwriter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/jsonwriter.cpp$(DependSuffix) -MM "jsonwriter.cpp"

$(IntermediateDirectory)/jsonwriter.cpp$(PreprocessSuffix): jsonwriter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jsonwriter.cpp$(PreprocessSuffix) "jsonwriter.cpp"

$(IntermediateDirectory)/language.cpp$(ObjectSuffix): language.cpp $(IntermediateDirectory)/language.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/language.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/language.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/language.cpp$(DependSuffix): language.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/language.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/language.cpp$(DependSuffix) -MM "language.cpp"

$(IntermediateDirectory)/language.cpp$(PreprocessSuffix): language.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/language.cpp$(PreprocessSuffix) "language.cpp"

$(IntermediateDirectory)/gui_v2capplication.cpp$(ObjectSuffix): gui_v2capplication.cpp $(IntermediateDirectory)/gui_v2capplication.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/gui_v2capplication.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gui_v2capplication.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui_v2capplication.cpp$(DependSuffix): gui_v2capplication.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui_v2capplication.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gui_v2capplication.cpp$(DependSuffix) -MM "gui_v2capplication.cpp"

$(IntermediateDirectory)/gui_v2capplication.cpp$(PreprocessSuffix): gui_v2capplication.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui_v2capplication.cpp$(PreprocessSuffix) "gui_v2capplication.cpp"

$(IntermediateDirectory)/v2capplication.cpp$(ObjectSuffix): v2capplication.cpp $(IntermediateDirectory)/v2capplication.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/v2capplication.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/v2capplication.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/v2capplication.cpp$(DependSuffix): v2capplication.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/v2capplication.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/v2capplication.cpp$(DependSuffix) -MM "v2capplication.cpp"

$(IntermediateDirectory)/v2capplication.cpp$(PreprocessSuffix): v2capplication.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/v2capplication.cpp$(PreprocessSuffix) "v2capplication.cpp"

$(IntermediateDirectory)/gui_v2ceditor.cpp$(ObjectSuffix): gui_v2ceditor.cpp $(IntermediateDirectory)/gui_v2ceditor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/gui_v2ceditor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gui_v2ceditor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui_v2ceditor.cpp$(DependSuffix): gui_v2ceditor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui_v2ceditor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gui_v2ceditor.cpp$(DependSuffix) -MM "gui_v2ceditor.cpp"

$(IntermediateDirectory)/gui_v2ceditor.cpp$(PreprocessSuffix): gui_v2ceditor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui_v2ceditor.cpp$(PreprocessSuffix) "gui_v2ceditor.cpp"

$(IntermediateDirectory)/v2ceditor.cpp$(ObjectSuffix): v2ceditor.cpp $(IntermediateDirectory)/v2ceditor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/v2ceditor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/v2ceditor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/v2ceditor.cpp$(DependSuffix): v2ceditor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/v2ceditor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/v2ceditor.cpp$(DependSuffix) -MM "v2ceditor.cpp"

$(IntermediateDirectory)/v2ceditor.cpp$(PreprocessSuffix): v2ceditor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/v2ceditor.cpp$(PreprocessSuffix) "v2ceditor.cpp"

$(IntermediateDirectory)/gui_activeword.cpp$(ObjectSuffix): gui_activeword.cpp $(IntermediateDirectory)/gui_activeword.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/gui_activeword.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gui_activeword.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui_activeword.cpp$(DependSuffix): gui_activeword.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui_activeword.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gui_activeword.cpp$(DependSuffix) -MM "gui_activeword.cpp"

$(IntermediateDirectory)/gui_activeword.cpp$(PreprocessSuffix): gui_activeword.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui_activeword.cpp$(PreprocessSuffix) "gui_activeword.cpp"

$(IntermediateDirectory)/activeword.cpp$(ObjectSuffix): activeword.cpp $(IntermediateDirectory)/activeword.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/activeword.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/activeword.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/activeword.cpp$(DependSuffix): activeword.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/activeword.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/activeword.cpp$(DependSuffix) -MM "activeword.cpp"

$(IntermediateDirectory)/activeword.cpp$(PreprocessSuffix): activeword.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/activeword.cpp$(PreprocessSuffix) "activeword.cpp"

$(IntermediateDirectory)/web.cpp$(ObjectSuffix): web.cpp $(IntermediateDirectory)/web.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/psc/src/kiku/kiku/web.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/web.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/web.cpp$(DependSuffix): web.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/web.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/web.cpp$(DependSuffix) -MM "web.cpp"

$(IntermediateDirectory)/web.cpp$(PreprocessSuffix): web.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/web.cpp$(PreprocessSuffix) "web.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


