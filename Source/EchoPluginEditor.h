/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef ECHOPLUGINEDITOR_H_INCLUDED
#define ECHOPLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EchoOperatorComponent.h"


//==============================================================================
/**
*/
class TestProject5AudioEchoProcessorEditor  : public AudioProcessorEditor
{
public:
    TestProject5AudioEchoProcessorEditor (EchoOperatorContentComponent&);
    ~TestProject5AudioEchoProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EchoOperatorContentComponent& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestProject5AudioEchoProcessorEditor)
};


#endif  // ECHOPLUGINEDITOR_H_INCLUDED
