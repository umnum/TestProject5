/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef SAMPLER1OPERATORCOMPONENT_H_INCLUDED
#define SAMPLER1OPERATORCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class Sampler1OperatorContentComponent   : public Component,
                                       public AudioProcessor,
                                       public HighResolutionTimer,
                                       public Slider::Listener,
                                       public ChangeListener
{
public:
    //==============================================================================
    Sampler1OperatorContentComponent();
    Sampler1OperatorContentComponent(Image, double);
    ~Sampler1OperatorContentComponent();

    void paint (Graphics&);
    void resized();
    void prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) override;
    const String getName() const override;
    void releaseResources() override;
    void updateAngleDelta();
    void mouseDown(const MouseEvent& e);
    void mouseDrag(const MouseEvent& e);
    void mouseDoubleClick(const MouseEvent& e);
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;
    bool isClicked();
    void setClicked(bool doubleClick);
    float getLevel();
    void setLevel(float level);
    double getFreq();
    void setFreq(double freq);
    //void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
    bool silenceInProducesSilenceOut()const override;
    double getTailLengthSeconds()const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;
    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    bool setTriggered(bool triggered);
    void setSustained(bool sustained);
    bool isSustained();
    void hiResTimerCallback();
    void initEnv(int envSize, int attackSize, int decaySize);
    float envTick();
    bool isMostRecentlyDoubleClicked();
    void setMostRecentlyDoubleClicked(bool mostRecentlyDoubleClicked);
    void changeListenerCallback(ChangeBroadcaster *source);
    //void processBlock(AudioBuffer<double>&buffer, MidiBuffer& midiMessages) override;
    //void processBlockBypassed(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
    //void processBlockBypassed(AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override;
    //bool setPreferredBusArrangement(bool isInputBus, int busIndex, const AudioChannelSet& preferredSet) override;
    //bool supportsDoublePrecisionProcessing() const override;
    //void reset() override;
    //void setNonRealtime(bool isNonRealtime) noexcept override;
    //int getNumParameters() override;
    //const String getParameterName(int parameterIndex) override;
    //float getParameter(int parameterIndex) override;
    //String getParameterName(int parameterIndex, int maximumStringLength) override;
    //const String getParameterText(int parameterIndex) override;
    //String getParameterText(int parameterIndex, int maximumStringLength) override;
    //int getParameterNumSteps(int parameterIndex) override;
    //float getParameterDefaultValue(int parameterIndex) override;
    //String getParameterLabel(int index) const override;
    //bool isParameterOrientationInverted(int index) const override;
    //void setParameter(int parameterIndex, float newValue) override;
    //bool isParameterAutomatable(int parameterIndex) const override;
    //bool isMetaParameter(int parameterIndex) const override;
    //void getCurrentProgramStateInformation(juce::MemoryBlock &destData) override;
    //void setCurrentProgramStateInformation(const void* data, int sizeInBytes) override;
    //void numChannelsChanged() override;
    //void addListener(AudioProcessorListener* newListener) override;
    //void removeListener(AudioProcessorListener *listenerToRemove) override;
    //void setPlayHead(AudioPlayHead* newPlayHead) override;
    //void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;


private:
    double currentSampleRate, currentAngle, angleDelta, freq;
    double *env;
    Image image;
    bool doubleClick;
    bool triggered;
    bool sustained;
    bool mostRecentlyDoubleClicked;
    int distance;
    float level;
    ComponentDragger myDragger;
    int pos;
    int timer;
    File *soundFile;
    AudioFormatManager formatManager;
    AudioTransportSource transportSource;
    TimeSliceThread thread;
    ScopedPointer<AudioFormatReaderSource> currentAudioFileSource;
    AudioDeviceManager deviceManager;
    AudioSourcePlayer audioSourcePlayer;
    AudioSampleBuffer fileBuffer;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sampler1OperatorContentComponent)
};


#endif  // SAMPLER1OPERATORCOMPONENT_H_INCLUDED
