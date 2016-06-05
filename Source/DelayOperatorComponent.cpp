/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include <src/main/jni/BinaryData.h>
#include <src/main/jni/AppConfig.h>
#include "DelayOperatorComponent.h"
#include "DelayPluginEditor.h"


//==============================================================================
    DelayOperatorContentComponent::DelayOperatorContentComponent() {
    }

DelayOperatorContentComponent::DelayOperatorContentComponent(Image image, double freq)
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
    }

    DelayOperatorContentComponent::~DelayOperatorContentComponent() {
        //shutdownAudio();
    }

    void DelayOperatorContentComponent::paint(Graphics &g) {
        g.drawImageWithin(image, 0, 0, getWidth(), getHeight(),
                          RectanglePlacement::onlyReduceInSize, false);
    }

    void DelayOperatorContentComponent::resized() {
        // This is called when the DelayOperatorContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        /*
        volSlider.setBounds(10,10,getWidth() - 20, 20);
        freqSlider.setBounds(10,30,getWidth() - 20, 20);
         */
    }

//=======================================================================
//void DelayOperatorContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
//{
  //  currentSampleRate = sampleRate;
 //   updateAngleDelta();
//}

    void DelayOperatorContentComponent::updateAngleDelta()
    {
        const double cyclesPerSample = freq / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

    void DelayOperatorContentComponent::processBlock(AudioBuffer<float> &buffer,
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
                    //data[i + numSamples*ch] *= currentSample * level + 1.0f;
                    /* echo */
                    //delayBuf[currentDelayIndex] = data[i + numSamples*ch] + delayBuf[delayIndex]*0.5f;
                    /* delay */
                    delayBuf[currentDelayIndex] = data[i + numSamples*ch];
                    data[i + numSamples*ch] += delayBuf[delayIndex];
                }
                currentDelayIndex++;
                delayIndex = currentDelayIndex - int((delayBufLength-1)*delay);
                if (currentDelayIndex >= delayBufLength)
                    currentDelayIndex = currentDelayIndex - delayBufLength;
                if (delayIndex < 0)
                    delayIndex = delayIndex + delayBufLength;
                if (delayIndex >= delayBufLength)
                    delayIndex = delayIndex - delayBufLength;
            }
    }

//void DelayOperatorContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
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


    void DelayOperatorContentComponent::releaseResources()
    {
        pos = 0;
    }

//=======================================================================

    void DelayOperatorContentComponent::mouseDown(const MouseEvent &e) {
        myDragger.startDraggingComponent(this, e);
    }

    void DelayOperatorContentComponent::mouseDrag(const MouseEvent &e) {
        myDragger.dragComponent(this, e, nullptr);
        //updateAngleDelta();
    }

    void DelayOperatorContentComponent::mouseDoubleClick(const MouseEvent &e) {
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

    void DelayOperatorContentComponent::sliderValueChanged(Slider *slider) {
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

    bool DelayOperatorContentComponent::isClicked() {
        return doubleClick;
    }

    void DelayOperatorContentComponent::setClicked(bool doubleClick) {
        this->doubleClick = doubleClick;
    }

    bool DelayOperatorContentComponent::isMostRecentlyDoubleClicked() {
        return mostRecentlyDoubleClicked;
    }

    void DelayOperatorContentComponent::setMostRecentlyDoubleClicked(
            bool mostRecentlyDoubleClicked) {
        this->mostRecentlyDoubleClicked = mostRecentlyDoubleClicked;
    }

    float DelayOperatorContentComponent::getLevel() {
        return level;
    }

    void DelayOperatorContentComponent::setLevel(float level) {
        this->level = level;
    }

    double DelayOperatorContentComponent::getFreq() {
        return freq;
    }

    void DelayOperatorContentComponent::setFreq(double freq) {
        this->freq = freq;
    }

    const String DelayOperatorContentComponent::getName() const {
        return JucePlugin_Name;
    }

    bool DelayOperatorContentComponent::acceptsMidi() const {
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool DelayOperatorContentComponent::silenceInProducesSilenceOut() const {
        return false;
    }
    double DelayOperatorContentComponent::getTailLengthSeconds() const {
        return 0.0;
    }

    int DelayOperatorContentComponent::getNumPrograms() {
        return 1;
    }

    int DelayOperatorContentComponent::getCurrentProgram() {
        return 0;
    }

    void DelayOperatorContentComponent::setCurrentProgram(int index) {
    }

    const String DelayOperatorContentComponent::getProgramName(int index) {
        return String();
    }

    void DelayOperatorContentComponent::changeProgramName(int index, const String &newName) {
    }

    bool DelayOperatorContentComponent::hasEditor() const {
        return true;
    }

    AudioProcessorEditor* DelayOperatorContentComponent::createEditor() {
        return new TestProject5AudioDelayProcessorEditor (*this);
    }

    void DelayOperatorContentComponent::getStateInformation(MemoryBlock &destData) {
    }

    void DelayOperatorContentComponent::setStateInformation(const void *data, int sizeInBytes) {
    }

    /*AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
        return new DelayOperatorContentComponent();
    }*/

    bool DelayOperatorContentComponent::producesMidi() const {
        return false;
    }

    void DelayOperatorContentComponent::sliderDragStarted(Slider *slider) {
    }

    void DelayOperatorContentComponent::sliderDragEnded(Slider *slider) {
    }

    void DelayOperatorContentComponent::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {
        currentSampleRate = sampleRate;
        Logger* log = Logger::getCurrentLogger();
        log->outputDebugString(String("The current sample rate is: " + String(currentSampleRate)));

        /* create a one second long delay buffer */
        delayBufLength = int(currentSampleRate);
        delayBuf = new float[delayBufLength];
        for (int i = 0; i < delayBufLength; ++i) {
            delayBuf[i] = 0.0f;
        }
        delay = 0.5;
        currentDelayIndex = delayBufLength-1;
        delayIndex = currentDelayIndex - int((delayBufLength-1)*delay);
    }

    double DelayOperatorContentComponent::getDelay() {
        return delay;
    }

    void DelayOperatorContentComponent::setDelay(double delay) {
        this->delay = delay;
    }

/*
void DelayOperatorContentComponent::processBlockBypassed(AudioBuffer<float> &buffer,
                                                     MidiBuffer &midiMessages) {
    AudioProcessor::processBlockBypassed(buffer, midiMessages);
}

bool DelayOperatorContentComponent::setPreferredBusArrangement(bool isInputBus, int busIndex,
                                                           const AudioChannelSet &preferredSet) {
    return AudioProcessor::setPreferredBusArrangement(isInputBus, busIndex, preferredSet);
}

bool DelayOperatorContentComponent::supportsDoublePrecisionProcessing() const {
    return AudioProcessor::supportsDoublePrecisionProcessing();
}

void DelayOperatorContentComponent::reset() {
    AudioProcessor::reset();
}

void DelayOperatorContentComponent::setNonRealtime(bool isNonRealtime) noexcept{
}

int DelayOperatorContentComponent::getNumParameters() {
    return AudioProcessor::getNumParameters();
}

const String DelayOperatorContentComponent::getParameterName(int parameterIndex) {
    return AudioProcessor::getParameterName(parameterIndex);
}

float DelayOperatorContentComponent::getParameter(int parameterIndex) {
    return AudioProcessor::getParameter(parameterIndex);
}

String DelayOperatorContentComponent::getParameterName(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterName(parameterIndex, maximumStringLength);
}

const String DelayOperatorContentComponent::getParameterText(int parameterIndex) {
    return AudioProcessor::getParameterText(parameterIndex);
}

String DelayOperatorContentComponent::getParameterText(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterText(parameterIndex, maximumStringLength);
}

int DelayOperatorContentComponent::getParameterNumSteps(int parameterIndex) {
    return AudioProcessor::getParameterNumSteps(parameterIndex);
}

float DelayOperatorContentComponent::getParameterDefaultValue(int parameterIndex) {
    return AudioProcessor::getParameterDefaultValue(parameterIndex);
}

String DelayOperatorContentComponent::getParameterLabel(int index) const {
    return AudioProcessor::getParameterLabel(index);
}

bool DelayOperatorContentComponent::isParameterOrientationInverted(int index) const {
    return AudioProcessor::isParameterOrientationInverted(index);
}

void DelayOperatorContentComponent::setParameter(int parameterIndex, float newValue) {
}

bool DelayOperatorContentComponent::isParameterAutomatable(int parameterIndex) const {
    return AudioProcessor::isParameterAutomatable(parameterIndex);
}

bool DelayOperatorContentComponent::isMetaParameter(int parameterIndex) const {
    return AudioProcessor::isMetaParameter(parameterIndex);
}

void DelayOperatorContentComponent::getCurrentProgramStateInformation(juce::MemoryBlock &destData) {
}

void DelayOperatorContentComponent::setCurrentProgramStateInformation(const void *data,
                                                                  int sizeInBytes) {
}

void DelayOperatorContentComponent::numChannelsChanged() {
}

void DelayOperatorContentComponent::addListener(AudioProcessorListener *newListener) {
}

void DelayOperatorContentComponent::removeListener(AudioProcessorListener *listenerToRemove) {
}

void DelayOperatorContentComponent::setPlayHead(AudioPlayHead *newPlayHead) {
}
*/

//void DelayOperatorContentComponent::processBlock(AudioBuffer<double> &buffer,
 //                                            MidiBuffer &midiMessages) {
//}

//void DelayOperatorContentComponent::processBlockBypassed(AudioBuffer<double> &buffer,
 //                                                    MidiBuffer &midiMessages) {
//}


