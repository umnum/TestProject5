# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_6D53C8B4=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../Programs/juce/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 

  TARGET := TestProject5
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_6D53C8B4=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../Programs/juce/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -O3
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 

  TARGET := TestProject5
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/DelayOperatorComponent_7a9f35ff.o \
  $(OBJDIR)/DelayPluginEditor_e998b84.o \
  $(OBJDIR)/EchoOperatorComponent_4b3a9a75.o \
  $(OBJDIR)/EchoPluginEditor_6702b54e.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/MainComponent_a6ffb4a5.o \
  $(OBJDIR)/PlayComponent_2fee2f0a.o \
  $(OBJDIR)/RadarTriggerComponent_5e51b72c.o \
  $(OBJDIR)/Sampler1OperatorComponent_bdc057f1.o \
  $(OBJDIR)/Sampler1PluginEditor_86037a52.o \
  $(OBJDIR)/SineOperatorComponent_e9d8770d.o \
  $(OBJDIR)/SinePluginEditor_58a359b6.o \
  $(OBJDIR)/TremoloOperatorComponent_6348d156.o \
  $(OBJDIR)/TremoloPluginEditor_1c73f5cd.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_81a7428d.o \
  $(OBJDIR)/juce_audio_devices_3a8c280b.o \
  $(OBJDIR)/juce_audio_formats_690d71ab.o \
  $(OBJDIR)/juce_audio_processors_41eb3f45.o \
  $(OBJDIR)/juce_audio_utils_43507d4b.o \
  $(OBJDIR)/juce_core_3798856f.o \
  $(OBJDIR)/juce_cryptography_832c45c9.o \
  $(OBJDIR)/juce_data_structures_d2592beb.o \
  $(OBJDIR)/juce_events_217ca263.o \
  $(OBJDIR)/juce_graphics_c3739847.o \
  $(OBJDIR)/juce_gui_basics_31538443.o \
  $(OBJDIR)/juce_gui_extra_d83fea8b.o \
  $(OBJDIR)/juce_opengl_e1c4ca8f.o \
  $(OBJDIR)/juce_PluginUtilities_844f517.o \
  $(OBJDIR)/juce_video_3f72c8ab.o \
  $(OBJDIR)/juce_VST_Wrapper_8e54d720.o \
  $(OBJDIR)/juce_VST3_Wrapper_5615c85e.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking TestProject5
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning TestProject5
	@$(CLEANCMD)

strip:
	@echo Stripping TestProject5
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/DelayOperatorComponent_7a9f35ff.o: ../../Source/DelayOperatorComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DelayOperatorComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DelayPluginEditor_e998b84.o: ../../Source/DelayPluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DelayPluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/EchoOperatorComponent_4b3a9a75.o: ../../Source/EchoOperatorComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling EchoOperatorComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/EchoPluginEditor_6702b54e.o: ../../Source/EchoPluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling EchoPluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainComponent_a6ffb4a5.o: ../../Source/MainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PlayComponent_2fee2f0a.o: ../../Source/PlayComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PlayComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RadarTriggerComponent_5e51b72c.o: ../../Source/RadarTriggerComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RadarTriggerComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Sampler1OperatorComponent_bdc057f1.o: ../../Source/Sampler1OperatorComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Sampler1OperatorComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Sampler1PluginEditor_86037a52.o: ../../Source/Sampler1PluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Sampler1PluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SineOperatorComponent_e9d8770d.o: ../../Source/SineOperatorComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SineOperatorComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SinePluginEditor_58a359b6.o: ../../Source/SinePluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SinePluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TremoloOperatorComponent_6348d156.o: ../../Source/TremoloOperatorComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TremoloOperatorComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TremoloPluginEditor_1c73f5cd.o: ../../Source/TremoloPluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TremoloPluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_81a7428d.o: ../../../Programs/juce/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_3a8c280b.o: ../../../Programs/juce/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_690d71ab.o: ../../../Programs/juce/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_41eb3f45.o: ../../../Programs/juce/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_43507d4b.o: ../../../Programs/juce/modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_3798856f.o: ../../../Programs/juce/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_832c45c9.o: ../../../Programs/juce/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_d2592beb.o: ../../../Programs/juce/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_217ca263.o: ../../../Programs/juce/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c3739847.o: ../../../Programs/juce/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_31538443.o: ../../../Programs/juce/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_d83fea8b.o: ../../../Programs/juce/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_e1c4ca8f.o: ../../../Programs/juce/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_844f517.o: ../../../Programs/juce/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_3f72c8ab.o: ../../../Programs/juce/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_8e54d720.o: ../../../Programs/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST3_Wrapper_5615c85e.o: ../../../Programs/juce/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST3_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
