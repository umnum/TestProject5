/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SineOperatorComponent.h"
#include "TremoloOperatorComponent.h"
#include "RadarTriggerComponent.h"
#include "Sampler1OperatorComponent.h"
#include "DelayOperatorComponent.h"
#include "EchoOperatorComponent.h"
#include "PlayComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               public ComponentListener,
                               public AudioProcessorPlayer,
                               public AudioProcessorGraph,
                               public HighResolutionTimer,
                               public Button::Listener,
                               public Slider::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    enum component{SINE, TREMOLO, RADAR, SAMP1, DELAY, ECHO, PLAY};
    void paint(Graphics&);
    void resized();
    void componentMovedOrResized(Component &component, bool wasMoved, bool wasResized);
    void buttonClicked(Button* button);
    void Reset();
    bool Connect(component componentType, bool hasInput, bool hasOutput);
    void prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) override;
    void hiResTimerCallback();
    void sliderValueChanged(Slider *slider);
    void mouseDoubleClick(const MouseEvent &event) override;

private:
    OwnedArray<Button> buttons;
    OwnedArray<SineOperatorContentComponent> sineOperators;
    OwnedArray<TremoloOperatorContentComponent> tremoloOperators;
    OwnedArray<Sampler1OperatorContentComponent> sampler1Operators;
    OwnedArray<DelayOperatorContentComponent> delayOperators;
    OwnedArray<EchoOperatorContentComponent> echoOperators;
    OwnedArray<PlayComponent> playOperators;
    OwnedArray<Node> sineNodes;
    OwnedArray<Node> tremoloNodes;
    OwnedArray<Node> samp1Nodes;
    OwnedArray<Node> delayNodes;
    OwnedArray<Node> echoNodes;
    OwnedArray<Slider> sineVolSlider;
    OwnedArray<Slider> sineFreqSlider;
    OwnedArray<Slider> tremoloIntensitySlider;
    OwnedArray<Slider> tremoloFreqSlider;
    OwnedArray<Slider> radarFreqSlider;
    OwnedArray<Slider> radarLengthSlider;
    OwnedArray<Slider> sampler1VolSlider;
    OwnedArray<Slider> delaySlider;
    OwnedArray<Slider> echoDelaySlider;
    OwnedArray<Slider> echoIntensitySlider;
    int radarRefresh;
    OwnedArray<RadarTriggerComponent> radarTriggers;
    Array<Image> image;
    TextButton resetButton;
    ScopedPointer<MixerAudioSource> source;
    AudioSourcePlayer player;
    AudioProcessorPlayer fPlayer;
    AudioProcessorGraph fGraph;
    AudioDeviceManager fDeviceManager;
    Node* fInputNode;
    Node* fOutputNode;
    AudioGraphIOProcessor* in;
    AudioGraphIOProcessor* out;
    int radarDistance;
    double tremoloDistance;
    //OwnedArray<AudioProcessorGraph::Node> nodes;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
