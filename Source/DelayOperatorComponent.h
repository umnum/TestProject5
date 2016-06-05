/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef DELAYOPERATORCOMPONENT_H_INCLUDED
#define DELAYOPERATORCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class DelayOperatorContentComponent   : public Component,
                                    public AudioProcessor,
                                   public Slider::Listener
{
public:
    //==============================================================================
    DelayOperatorContentComponent();
    DelayOperatorContentComponent(Image, double);
    ~DelayOperatorContentComponent();

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
    bool isMostRecentlyDoubleClicked();
    void setMostRecentlyDoubleClicked(bool mostRecentlyDoubleClicked);
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
    double getDelay();
    void setDelay(double delay);
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
    Image image;
    bool doubleClick;
    bool mostRecentlyDoubleClicked;
    int distance;
    float level;
    float *delayBuf;
    int delayBufLength;
    int delayIndex;
    int currentDelayIndex;
    //Slider volSlider;
    //Slider freqSlider;
    ComponentDragger myDragger;
    int pos;
    double delay;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayOperatorContentComponent)
};


#endif  // DELAYOPERATORCOMPONENT_H_INCLUDED
