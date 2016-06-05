/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include <src/main/jni/BinaryData.h>
#include <src/main/jni/AppConfig.h>
#include "TremoloOperatorComponent.h"
#include "TremoloPluginEditor.h"


//==============================================================================
    TremoloOperatorContentComponent::TremoloOperatorContentComponent() {
    }

TremoloOperatorContentComponent::TremoloOperatorContentComponent(Image image, double freq)
    :   currentSampleRate(0.0),
        currentAngle(0.0),
        angleDelta(0.0),
        doubleClick(false),
        distance(0),
        pos(0),
        level(1)
    {
        this->image = image;
        this->freq = freq;
        /*addAndMakeVisible(volSlider);
        addAndMakeVisible(freqSlider);
        volSlider.setVisible(false);
        volSlider.setRange(0.0,1.0);
        volSlider.addListener(this);
        freqSlider.setVisible(false);
        freqSlider.setRange(0.0,50.0);
        //freqSlider.setSkewFactorFromMidPoint(5.0);
        freqSlider.addListener(this);
        //setAudioChannels(0,1);*/
    }

    TremoloOperatorContentComponent::~TremoloOperatorContentComponent() {
        //shutdownAudio();
    }

    void TremoloOperatorContentComponent::paint(Graphics &g) {
        g.drawImageWithin(image, 0, 0, getWidth(), getHeight(),
                          RectanglePlacement::onlyReduceInSize, false);
    }

    void TremoloOperatorContentComponent::resized() {
        // This is called when the TremoloOperatorContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        /*
        volSlider.setBounds(10,10,getWidth() - 20, 20);
        freqSlider.setBounds(10,30,getWidth() - 20, 20);
         */
    }

//=======================================================================
//void TremoloOperatorContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
//{
  //  currentSampleRate = sampleRate;
 //   updateAngleDelta();
//}

    void TremoloOperatorContentComponent::updateAngleDelta()
    {
        const double cyclesPerSample = freq / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

    void TremoloOperatorContentComponent::processBlock(AudioBuffer<float> &buffer,
                                                 MidiBuffer &midiMessages) {
        //for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
        int numSamples = buffer.getNumSamples();
        int numChannels = buffer.getNumChannels();
            float *data = buffer.getWritePointer(0);
            for (int i = 0; i < numSamples; ++i) {
                //data[i] = std::sin(2.0f*float_Pi*freq*static_cast<float>(pos++)/currentSampleRate)*level;
                const float currentSample = (float) std::sin(currentAngle);
                currentAngle += angleDelta;
                for (int ch = 0; ch < numChannels; ++ch) {
                    data[i + numSamples*ch] *= currentSample * level + 1.0f;
                }
            }
    }

//void TremoloOperatorContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
//{
    /*
    float * const buffer = bufferToFill.buffer->getWritePointer(0);

    for (int sample = 0; sample < bufferToFill.buffer->getNumSamples(); ++sample)
    {
        const float currentSample = (float) std::sin (currentAngle);
        currentAngle += angleDelta;
        buffer[sample] = (buffer[sample]*currentSample + 1.0f)*0.5f*level;
    }
     */
//}


    void TremoloOperatorContentComponent::releaseResources()
    {
        pos = 0;
    }

//=======================================================================

    void TremoloOperatorContentComponent::mouseDown(const MouseEvent &e) {
        myDragger.startDraggingComponent(this, e);
    }

    void TremoloOperatorContentComponent::mouseDrag(const MouseEvent &e) {
        myDragger.dragComponent(this, e, nullptr);
        //updateAngleDelta();
    }

    void TremoloOperatorContentComponent::mouseDoubleClick(const MouseEvent &e) {
        Logger* log = Logger::getCurrentLogger();
        log->outputDebugString("double click");
        if (doubleClick) {
            //volSlider.setVisible(false);
            //freqSlider.setVisible(false);
            doubleClick = false;
            mostRecentlyDoubleClicked = false;
        }
        else {
            //volSlider.setVisible(true);
            //freqSlider.setVisible(true);
            doubleClick = true;
        }
    }

    void TremoloOperatorContentComponent::sliderValueChanged(Slider *slider) {
        /*if (slider == &volSlider){
            level = volSlider.getValue();
        }
        if (slider == &freqSlider){
            Logger *log = Logger::getCurrentLogger();
            freq = freqSlider.getValue();
            updateAngleDelta();
            log->outputDebugString(String(freq));
        }*/
    }

    bool TremoloOperatorContentComponent::isClicked() {
        return doubleClick;
    }

    void TremoloOperatorContentComponent::setClicked(bool doubleClick) {
        this->doubleClick = doubleClick;
    }

    bool TremoloOperatorContentComponent::isMostRecentlyDoubleClicked() {
        return mostRecentlyDoubleClicked;
    }

    void TremoloOperatorContentComponent::setMostRecentlyDoubleClicked(
            bool mostRecentlyDoubleClicked) {
        this->mostRecentlyDoubleClicked = mostRecentlyDoubleClicked;
    }

    float TremoloOperatorContentComponent::getLevel() {
        return level;
    }

    void TremoloOperatorContentComponent::setLevel(float level) {
        this->level = level;
    }

    double TremoloOperatorContentComponent::getFreq() {
        return freq;
    }

    void TremoloOperatorContentComponent::setFreq(double freq) {
        this->freq = freq;
    }

    const String TremoloOperatorContentComponent::getName() const {
        return JucePlugin_Name;
    }

    bool TremoloOperatorContentComponent::acceptsMidi() const {
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool TremoloOperatorContentComponent::silenceInProducesSilenceOut() const {
        return false;
    }
    double TremoloOperatorContentComponent::getTailLengthSeconds() const {
        return 0.0;
    }

    int TremoloOperatorContentComponent::getNumPrograms() {
        return 1;
    }

    int TremoloOperatorContentComponent::getCurrentProgram() {
        return 0;
    }

    void TremoloOperatorContentComponent::setCurrentProgram(int index) {
    }

    const String TremoloOperatorContentComponent::getProgramName(int index) {
        return String();
    }

    void TremoloOperatorContentComponent::changeProgramName(int index, const String &newName) {
    }

    bool TremoloOperatorContentComponent::hasEditor() const {
        return true;
    }

    AudioProcessorEditor* TremoloOperatorContentComponent::createEditor() {
        return new TestProject5AudioTremoloProcessorEditor (*this);
    }

    void TremoloOperatorContentComponent::getStateInformation(MemoryBlock &destData) {
    }

    void TremoloOperatorContentComponent::setStateInformation(const void *data, int sizeInBytes) {
    }

    /*AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
        return new TremoloOperatorContentComponent();
    }*/

    bool TremoloOperatorContentComponent::producesMidi() const {
        return false;
    }

    void TremoloOperatorContentComponent::sliderDragStarted(Slider *slider) {
    }

    void TremoloOperatorContentComponent::sliderDragEnded(Slider *slider) {
    }

    void TremoloOperatorContentComponent::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {
        currentSampleRate = sampleRate;
        Logger* log = Logger::getCurrentLogger();
        log->outputDebugString(String("The current sample rate is: " + String(currentSampleRate)));
    }

/*
void TremoloOperatorContentComponent::processBlockBypassed(AudioBuffer<float> &buffer,
                                                     MidiBuffer &midiMessages) {
    AudioProcessor::processBlockBypassed(buffer, midiMessages);
}

bool TremoloOperatorContentComponent::setPreferredBusArrangement(bool isInputBus, int busIndex,
                                                           const AudioChannelSet &preferredSet) {
    return AudioProcessor::setPreferredBusArrangement(isInputBus, busIndex, preferredSet);
}

bool TremoloOperatorContentComponent::supportsDoublePrecisionProcessing() const {
    return AudioProcessor::supportsDoublePrecisionProcessing();
}

void TremoloOperatorContentComponent::reset() {
    AudioProcessor::reset();
}

void TremoloOperatorContentComponent::setNonRealtime(bool isNonRealtime) noexcept{
}

int TremoloOperatorContentComponent::getNumParameters() {
    return AudioProcessor::getNumParameters();
}

const String TremoloOperatorContentComponent::getParameterName(int parameterIndex) {
    return AudioProcessor::getParameterName(parameterIndex);
}

float TremoloOperatorContentComponent::getParameter(int parameterIndex) {
    return AudioProcessor::getParameter(parameterIndex);
}

String TremoloOperatorContentComponent::getParameterName(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterName(parameterIndex, maximumStringLength);
}

const String TremoloOperatorContentComponent::getParameterText(int parameterIndex) {
    return AudioProcessor::getParameterText(parameterIndex);
}

String TremoloOperatorContentComponent::getParameterText(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterText(parameterIndex, maximumStringLength);
}

int TremoloOperatorContentComponent::getParameterNumSteps(int parameterIndex) {
    return AudioProcessor::getParameterNumSteps(parameterIndex);
}

float TremoloOperatorContentComponent::getParameterDefaultValue(int parameterIndex) {
    return AudioProcessor::getParameterDefaultValue(parameterIndex);
}

String TremoloOperatorContentComponent::getParameterLabel(int index) const {
    return AudioProcessor::getParameterLabel(index);
}

bool TremoloOperatorContentComponent::isParameterOrientationInverted(int index) const {
    return AudioProcessor::isParameterOrientationInverted(index);
}

void TremoloOperatorContentComponent::setParameter(int parameterIndex, float newValue) {
}

bool TremoloOperatorContentComponent::isParameterAutomatable(int parameterIndex) const {
    return AudioProcessor::isParameterAutomatable(parameterIndex);
}

bool TremoloOperatorContentComponent::isMetaParameter(int parameterIndex) const {
    return AudioProcessor::isMetaParameter(parameterIndex);
}

void TremoloOperatorContentComponent::getCurrentProgramStateInformation(juce::MemoryBlock &destData) {
}

void TremoloOperatorContentComponent::setCurrentProgramStateInformation(const void *data,
                                                                  int sizeInBytes) {
}

void TremoloOperatorContentComponent::numChannelsChanged() {
}

void TremoloOperatorContentComponent::addListener(AudioProcessorListener *newListener) {
}

void TremoloOperatorContentComponent::removeListener(AudioProcessorListener *listenerToRemove) {
}

void TremoloOperatorContentComponent::setPlayHead(AudioPlayHead *newPlayHead) {
}
*/

//void TremoloOperatorContentComponent::processBlock(AudioBuffer<double> &buffer,
 //                                            MidiBuffer &midiMessages) {
//}

//void TremoloOperatorContentComponent::processBlockBypassed(AudioBuffer<double> &buffer,
 //                                                    MidiBuffer &midiMessages) {
//}


