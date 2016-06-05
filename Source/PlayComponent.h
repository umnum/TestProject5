/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef PLAYCOMPONENT_H_INCLUDED
#define PLAYCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class PlayComponent   : public Component,
                                public Slider::Listener
{
public:
    //==============================================================================
    PlayComponent();
    PlayComponent(Image);
    ~PlayComponent();

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
    bool isClicked();
    void setClicked(bool doubleClick);
    float getLevel();
    void withinTriggerDistance(int kOperatorIndex, bool isWithinDistance);
    bool isWithinTriggerDistance(int kOperatorIndex);
    void sampler1WithinTriggerDistance(int sampler1Index, bool isWithinDistance);
    bool sampler1IsWithinTriggerDistance(int sampler1Index);
    bool isMostRecentlyDoubleClicked();
    void setMostRecentlyDoubleClicked(bool mostRecentlyDoubleClicked);
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
    Image image;
    bool doubleClick;
    bool mostRecentlyDoubleClicked;
    Array<bool> isWithinDistance;
    Array<bool> sampler1IsWithinDistance;
    int distance;
    float level;
    ComponentDragger myDragger;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayComponent)
};


#endif  // PLAYCOMPONENT_H_INCLUDED
