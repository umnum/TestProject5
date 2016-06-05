/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include <src/main/jni/BinaryData.h>
#include <src/main/jni/AppConfig.h>
#include "EchoOperatorComponent.h"
#include "EchoPluginEditor.h"


//==============================================================================
    EchoOperatorContentComponent::EchoOperatorContentComponent() {
    }

EchoOperatorContentComponent::EchoOperatorContentComponent(Image image, double freq)
    :   currentSampleRate(0.0),
        currentAngle(0.0),
        angleDelta(0.0),
        doubleClick(false),
        distance(0),
        pos(0),
        intensity(0.5f),
        level(1)
    {
        this->image = image;
        this->freq = freq;
    }

    EchoOperatorContentComponent::~EchoOperatorContentComponent() {
        //shutdownAudio();
    }

    void EchoOperatorContentComponent::paint(Graphics &g) {
        g.drawImageWithin(image, 0, 0, getWidth(), getHeight(),
                          RectanglePlacement::onlyReduceInSize, false);
    }

    void EchoOperatorContentComponent::resized() {
        // This is called when the EchoOperatorContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        /*
        volSlider.setBounds(10,10,getWidth() - 20, 20);
        freqSlider.setBounds(10,30,getWidth() - 20, 20);
         */
    }

//=======================================================================
//void EchoOperatorContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
//{
  //  currentSampleRate = sampleRate;
 //   updateAngleDelta();
//}

    void EchoOperatorContentComponent::updateAngleDelta()
    {
        const double cyclesPerSample = freq / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

    void EchoOperatorContentComponent::processBlock(AudioBuffer<float> &buffer,
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
                    delayBuf[currentEchoIndex] = data[i + numSamples*ch] + delayBuf[delayIndex]*intensity;
                    /* delay */
                    //delayBuf[currentEchoIndex] = data[i + numSamples*ch];
                    data[i + numSamples*ch] += delayBuf[delayIndex];
                }
                currentEchoIndex++;
                delayIndex = currentEchoIndex - int((delayBufLength-1)*delay);
                if (currentEchoIndex >= delayBufLength)
                    currentEchoIndex = currentEchoIndex - delayBufLength;
                if (delayIndex < 0)
                    delayIndex = delayIndex + delayBufLength;
                if (delayIndex >= delayBufLength)
                    delayIndex = delayIndex - delayBufLength;
            }
    }

//void EchoOperatorContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
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


    void EchoOperatorContentComponent::releaseResources()
    {
        pos = 0;
    }

//=======================================================================

    void EchoOperatorContentComponent::mouseDown(const MouseEvent &e) {
        myDragger.startDraggingComponent(this, e);
    }

    void EchoOperatorContentComponent::mouseDrag(const MouseEvent &e) {
        myDragger.dragComponent(this, e, nullptr);
        //updateAngleDelta();
    }

    void EchoOperatorContentComponent::mouseDoubleClick(const MouseEvent &e) {
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

    void EchoOperatorContentComponent::sliderValueChanged(Slider *slider) {
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

    bool EchoOperatorContentComponent::isClicked() {
        return doubleClick;
    }

    void EchoOperatorContentComponent::setClicked(bool doubleClick) {
        this->doubleClick = doubleClick;
    }

    bool EchoOperatorContentComponent::isMostRecentlyDoubleClicked() {
        return mostRecentlyDoubleClicked;
    }

    void EchoOperatorContentComponent::setMostRecentlyDoubleClicked(
            bool mostRecentlyDoubleClicked) {
        this->mostRecentlyDoubleClicked = mostRecentlyDoubleClicked;
    }

    float EchoOperatorContentComponent::getLevel() {
        return level;
    }

    void EchoOperatorContentComponent::setLevel(float level) {
        this->level = level;
    }

    double EchoOperatorContentComponent::getFreq() {
        return freq;
    }

    void EchoOperatorContentComponent::setFreq(double freq) {
        this->freq = freq;
    }

    const String EchoOperatorContentComponent::getName() const {
        return JucePlugin_Name;
    }

    bool EchoOperatorContentComponent::acceptsMidi() const {
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool EchoOperatorContentComponent::silenceInProducesSilenceOut() const {
        return false;
    }
    double EchoOperatorContentComponent::getTailLengthSeconds() const {
        return 0.0;
    }

    int EchoOperatorContentComponent::getNumPrograms() {
        return 1;
    }

    int EchoOperatorContentComponent::getCurrentProgram() {
        return 0;
    }

    void EchoOperatorContentComponent::setCurrentProgram(int index) {
    }

    const String EchoOperatorContentComponent::getProgramName(int index) {
        return String();
    }

    void EchoOperatorContentComponent::changeProgramName(int index, const String &newName) {
    }

    bool EchoOperatorContentComponent::hasEditor() const {
        return true;
    }

    AudioProcessorEditor* EchoOperatorContentComponent::createEditor() {
        return new TestProject5AudioEchoProcessorEditor (*this);
    }

    void EchoOperatorContentComponent::getStateInformation(MemoryBlock &destData) {
    }

    void EchoOperatorContentComponent::setStateInformation(const void *data, int sizeInBytes) {
    }

    /*AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
        return new EchoOperatorContentComponent();
    }*/

    bool EchoOperatorContentComponent::producesMidi() const {
        return false;
    }

    void EchoOperatorContentComponent::sliderDragStarted(Slider *slider) {
    }

    void EchoOperatorContentComponent::sliderDragEnded(Slider *slider) {
    }

    void EchoOperatorContentComponent::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {
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
        currentEchoIndex = delayBufLength-1;
        delayIndex = currentEchoIndex - int((delayBufLength-1)*delay);
    }

    double EchoOperatorContentComponent::getEchoDelay() {
        return delay;
    }

    void EchoOperatorContentComponent::setEchoDelay(double delay) {
        this->delay = delay;
    }

    float EchoOperatorContentComponent::getEchoIntensity() {
        return intensity;
    }

    void EchoOperatorContentComponent::setEchoIntensity(float intensity) {
        this->intensity = intensity;
    }
/*
void EchoOperatorContentComponent::processBlockBypassed(AudioBuffer<float> &buffer,
                                                     MidiBuffer &midiMessages) {
    AudioProcessor::processBlockBypassed(buffer, midiMessages);
}

bool EchoOperatorContentComponent::setPreferredBusArrangement(bool isInputBus, int busIndex,
                                                           const AudioChannelSet &preferredSet) {
    return AudioProcessor::setPreferredBusArrangement(isInputBus, busIndex, preferredSet);
}

bool EchoOperatorContentComponent::supportsDoublePrecisionProcessing() const {
    return AudioProcessor::supportsDoublePrecisionProcessing();
}

void EchoOperatorContentComponent::reset() {
    AudioProcessor::reset();
}

void EchoOperatorContentComponent::setNonRealtime(bool isNonRealtime) noexcept{
}

int EchoOperatorContentComponent::getNumParameters() {
    return AudioProcessor::getNumParameters();
}

const String EchoOperatorContentComponent::getParameterName(int parameterIndex) {
    return AudioProcessor::getParameterName(parameterIndex);
}

float EchoOperatorContentComponent::getParameter(int parameterIndex) {
    return AudioProcessor::getParameter(parameterIndex);
}

String EchoOperatorContentComponent::getParameterName(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterName(parameterIndex, maximumStringLength);
}

const String EchoOperatorContentComponent::getParameterText(int parameterIndex) {
    return AudioProcessor::getParameterText(parameterIndex);
}

String EchoOperatorContentComponent::getParameterText(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterText(parameterIndex, maximumStringLength);
}

int EchoOperatorContentComponent::getParameterNumSteps(int parameterIndex) {
    return AudioProcessor::getParameterNumSteps(parameterIndex);
}

float EchoOperatorContentComponent::getParameterDefaultValue(int parameterIndex) {
    return AudioProcessor::getParameterDefaultValue(parameterIndex);
}

String EchoOperatorContentComponent::getParameterLabel(int index) const {
    return AudioProcessor::getParameterLabel(index);
}

bool EchoOperatorContentComponent::isParameterOrientationInverted(int index) const {
    return AudioProcessor::isParameterOrientationInverted(index);
}

void EchoOperatorContentComponent::setParameter(int parameterIndex, float newValue) {
}

bool EchoOperatorContentComponent::isParameterAutomatable(int parameterIndex) const {
    return AudioProcessor::isParameterAutomatable(parameterIndex);
}

bool EchoOperatorContentComponent::isMetaParameter(int parameterIndex) const {
    return AudioProcessor::isMetaParameter(parameterIndex);
}

void EchoOperatorContentComponent::getCurrentProgramStateInformation(juce::MemoryBlock &destData) {
}

void EchoOperatorContentComponent::setCurrentProgramStateInformation(const void *data,
                                                                  int sizeInBytes) {
}

void EchoOperatorContentComponent::numChannelsChanged() {
}

void EchoOperatorContentComponent::addListener(AudioProcessorListener *newListener) {
}

void EchoOperatorContentComponent::removeListener(AudioProcessorListener *listenerToRemove) {
}

void EchoOperatorContentComponent::setPlayHead(AudioPlayHead *newPlayHead) {
}
*/

//void EchoOperatorContentComponent::processBlock(AudioBuffer<double> &buffer,
 //                                            MidiBuffer &midiMessages) {
//}

//void EchoOperatorContentComponent::processBlockBypassed(AudioBuffer<double> &buffer,
 //                                                    MidiBuffer &midiMessages) {
//}


