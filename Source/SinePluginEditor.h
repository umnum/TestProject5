/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef SINEPLUGINEDITOR_H_INCLUDED
#define SINEPLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SineOperatorComponent.h"


//==============================================================================
/**
*/
class TestProject5AudioSineProcessorEditor  : public AudioProcessorEditor
{
public:
    TestProject5AudioSineProcessorEditor (SineOperatorContentComponent&);
    ~TestProject5AudioSineProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SineOperatorContentComponent& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestProject5AudioSineProcessorEditor)
};


#endif  // SINEPLUGINEDITOR_H_INCLUDED