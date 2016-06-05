/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef RADARTRIGGERCOMPONENT_H_INCLUDED
#define RADARTRIGGERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class RadarTriggerComponent   : public Component,
                                public HighResolutionTimer,
                                public Slider::Listener
{
public:
    //==============================================================================
    RadarTriggerComponent();
    RadarTriggerComponent(Image, double);
    ~RadarTriggerComponent();

    void paint (Graphics&);
    void resized();
    //const String getName() const override;
    //void releaseResources() override;
    void updateAngleDelta();
    void mouseDown(const MouseEvent& e);
    void mouseDrag(const MouseEvent& e);
    void mouseDoubleClick(const MouseEvent& e);
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;
    void hiResTimerCallback();
    bool isClicked();
    void setClicked(bool doubleClick);
    float getLevel();
    double getTheta();
    void setTheta(double theta);
    double getFreq();
    void setFreq(double freq);
    void setAngleBetween(int kOperatorIndex, double angle);
    double getAngleBetween(int kOperatorIndex);
    void withinTriggerDistance(int kOperatorIndex, bool isWithinDistance);
    bool isWithinTriggerDistance(int kOperatorIndex);
    bool isMostRecentlyDoubleClicked();
    void setMostRecentlyDoubleClicked(bool mostRecentlyDoubleClicked);
    int getRadarDistance();
    void setRadarDistance(int radarDistance);
    //void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
    //bool silenceInProducesSilenceOut()const override;
    //double getTailLengthSeconds()const override;
    //bool acceptsMidi() const override;
    //bool producesMidi() const override;
    //AudioProcessorEditor* createEditor() override;
    //bool hasEditor() const override;
    //int getNumPrograms() override;
    //int getCurrentProgram() override;
    //void setCurrentProgram(int index) override;
    //const String getProgramName(int index) override;
    //void changeProgramName(int index, const String& newName) override;
    //void getStateInformation(MemoryBlock& destData) override;
    //void setStateInformation(const void* data, int sizeInBytes) override;


private:
    double angleDelta, freq, theta;
    Array<double> angles;
    Image image;
    bool doubleClick;
    bool mostRecentlyDoubleClicked;
    Array<bool> isWithinDistance;
    int distance;
    float level;
    ComponentDragger myDragger;
    int counter;
    int radarDistance;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadarTriggerComponent)
};


#endif  // RADARTRIGGERCOMPONENT_H_INCLUDED
