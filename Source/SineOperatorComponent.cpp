/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include <src/main/jni/BinaryData.h>
#include <src/main/jni/AppConfig.h>
#include "SineOperatorComponent.h"
#include "SinePluginEditor.h"
#include "MainComponent.h"


//==============================================================================
    SineOperatorContentComponent::SineOperatorContentComponent()
    //: thread("audio file preview")
    {
    }

SineOperatorContentComponent::SineOperatorContentComponent(Image image, double freq)
    :   currentSampleRate(0.0),
        currentAngle(0.0),
        angleDelta(0.0),
        doubleClick(false),
        distance(0),
        pos(0),
        level(0.5),
        triggered(false),
        sustained(false),
        timer(0)
        //thread("audio file preview")
    {
        this->image = image;
        this->freq = freq;
        //setAudioChannels(0,1);
    }

    SineOperatorContentComponent::~SineOperatorContentComponent() {
        Logger* log = Logger::getCurrentLogger();
        delete(env);
        log->outputDebugString("Sine Destructor Called ");
        //shutdownAudio();
    }

    void SineOperatorContentComponent::paint(Graphics &g) {
        g.drawImageWithin(image, 0, 0, getWidth(), getHeight(),
                          RectanglePlacement::onlyReduceInSize, false);
    }

    void SineOperatorContentComponent::resized() {
        // This is called when the SineOperatorContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

//=======================================================================
//void SineOperatorContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
//{
  //  currentSampleRate = sampleRate;
 //   updateAngleDelta();
//}

    void SineOperatorContentComponent::updateAngleDelta()
    {
        const double cyclesPerSample = freq / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

    void SineOperatorContentComponent::processBlock(AudioBuffer<float> &buffer,
                                                 MidiBuffer &midiMessages) {
        //for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
        float env;
        int numSamples = buffer.getNumSamples();
        /*AudioSourceChannelInfo *audioSourceChannelInfo = new AudioSourceChannelInfo(
                &buffer, 0, numSamples);
        transportSource.getNextAudioBlock(*audioSourceChannelInfo);
         */
        int numChannels = buffer.getNumChannels();
        float *data = buffer.getWritePointer(0);

        for (int i = 0; i < numSamples; ++i) {
            const float currentSample = (float) std::sin(currentAngle);
            currentAngle += angleDelta;
            env = envTick();
            for (int ch = 0; ch < numChannels; ++ch) {
                //buffer.copyFrom(ch, 0, fileBuffer, ch % fileBuffer.getNumChannels(), 0, numSamples);
                data[i + numSamples * ch] = currentSample * level * 0.5f * env;
                //data[i + numSamples * ch] = *(float *) audioSourceChannelInfo->buffer;
            }
        }
    }

    void SineOperatorContentComponent::initEnv(int envSize, int attackSize, int decaySize) {
        if (attackSize+decaySize>envSize) {
            attackSize = decaySize = 0;
        }
        env = new double[4*envSize];
        double slope = 1.0/double(attackSize);
        for (int i = 0; i < attackSize; ++i) {
            env[i] = double(i)*slope;
        }
        for (int i = attackSize; i < envSize-decaySize; ++i) {
            env[i] = 1.0;
        }
        slope = -1.0/double(decaySize);
        for (int i = envSize-decaySize; i < envSize; ++i) {
            env[i] = slope*double(i-(envSize-decaySize)) + 1.0;
        }
        this->envSize = envSize;
        this->attackSize = attackSize;
        this->decaySize = decaySize;
    }

    float SineOperatorContentComponent::envTick() {
        if (triggered) {
            if (pos != envSize - attackSize || !sustained)
                pos++;
            return float(env[pos]);
        }
        else {
            pos = 0;
            return 0.0f;
        }
    }

//void SineOperatorContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
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


    void SineOperatorContentComponent::releaseResources()
    {
        pos = 0;
    }

//=======================================================================

    void SineOperatorContentComponent::mouseDown(const MouseEvent &e) {
        myDragger.startDraggingComponent(this, e);
    }

    void SineOperatorContentComponent::mouseDrag(const MouseEvent &e) {
        myDragger.dragComponent(this, e, nullptr);
        updateAngleDelta();
    }

    void SineOperatorContentComponent::mouseDoubleClick(const MouseEvent &e) {
        Logger* log = Logger::getCurrentLogger();
        log->outputDebugString("double click");
        if (doubleClick) {
            doubleClick = false;
            mostRecentlyDoubleClicked = false;
        }
        else {
            doubleClick = true;
        }
    }

    void SineOperatorContentComponent::sliderValueChanged(Slider *slider) {
    }

    bool SineOperatorContentComponent::isClicked() {
        return doubleClick;
    }

    void SineOperatorContentComponent::setClicked(bool doubleClick) {
        this->doubleClick = doubleClick;
    }

    bool SineOperatorContentComponent::isMostRecentlyDoubleClicked() {
        return mostRecentlyDoubleClicked;
    }

    void SineOperatorContentComponent::setMostRecentlyDoubleClicked(
            bool mostRecentlyDoubleClicked) {
        this->mostRecentlyDoubleClicked = mostRecentlyDoubleClicked;
    }

    float SineOperatorContentComponent::getLevel() {
        return level;
    }

    void SineOperatorContentComponent::setLevel(float level) {
        this->level = level;
    }

    double SineOperatorContentComponent::getFreq() {
        return freq;
    }

    void SineOperatorContentComponent::setFreq(double freq) {
        this->freq = freq;
    }

    const String SineOperatorContentComponent::getName() const {
        return JucePlugin_Name;
    }

    bool SineOperatorContentComponent::acceptsMidi() const {
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool SineOperatorContentComponent::silenceInProducesSilenceOut() const {
        return false;
    }
    double SineOperatorContentComponent::getTailLengthSeconds() const {
        return 0.0;
    }

    int SineOperatorContentComponent::getNumPrograms() {
        return 1;
    }

    int SineOperatorContentComponent::getCurrentProgram() {
        return 0;
    }

    void SineOperatorContentComponent::setCurrentProgram(int index) {
    }

    const String SineOperatorContentComponent::getProgramName(int index) {
        return String();
    }

    void SineOperatorContentComponent::changeProgramName(int index, const String &newName) {
    }

    bool SineOperatorContentComponent::hasEditor() const {
        return true;
    }

    AudioProcessorEditor* SineOperatorContentComponent::createEditor() {
        return new TestProject5AudioSineProcessorEditor (*this);
    }

    void SineOperatorContentComponent::getStateInformation(MemoryBlock &destData) {
    }

    void SineOperatorContentComponent::setStateInformation(const void *data, int sizeInBytes) {
    }

    AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
        return new SineOperatorContentComponent();
    }

    bool SineOperatorContentComponent::producesMidi() const {
        return false;
    }

    void SineOperatorContentComponent::sliderDragStarted(Slider *slider) {
    }

    void SineOperatorContentComponent::sliderDragEnded(Slider *slider) {
    }

    void SineOperatorContentComponent::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {
        currentSampleRate = sampleRate;
        int envSize = int(currentSampleRate/10.0);
        int attackSize = int(envSize/8.0);
        int decaySize = attackSize;
        initEnv(envSize, attackSize, decaySize);
    }

    bool SineOperatorContentComponent::setTriggered(bool triggered) {
        if (triggered && !this->triggered)
            timer = 100;
        if (!triggered)
            pos = 0;
        this->triggered = triggered;
    }

    bool SineOperatorContentComponent::setSustained(bool sustained) {
        this->sustained = sustained;
    }

    void SineOperatorContentComponent::hiResTimerCallback() {
        if(triggered && !sustained)
            timer--;
        if (!timer)
            triggered = false;
    }

    void SineOperatorContentComponent::changeListenerCallback(ChangeBroadcaster *source) {
    }

/*
void SineOperatorContentComponent::processBlockBypassed(AudioBuffer<float> &buffer,
                                                     MidiBuffer &midiMessages) {
    AudioProcessor::processBlockBypassed(buffer, midiMessages);
}

bool SineOperatorContentComponent::setPreferredBusArrangement(bool isInputBus, int busIndex,
                                                           const AudioChannelSet &preferredSet) {
    return AudioProcessor::setPreferredBusArrangement(isInputBus, busIndex, preferredSet);
}

bool SineOperatorContentComponent::supportsDoublePrecisionProcessing() const {
    return AudioProcessor::supportsDoublePrecisionProcessing();
}

void SineOperatorContentComponent::reset() {
    AudioProcessor::reset();
}

void SineOperatorContentComponent::setNonRealtime(bool isNonRealtime) noexcept{
}

int SineOperatorContentComponent::getNumParameters() {
    return AudioProcessor::getNumParameters();
}

const String SineOperatorContentComponent::getParameterName(int parameterIndex) {
    return AudioProcessor::getParameterName(parameterIndex);
}

float SineOperatorContentComponent::getParameter(int parameterIndex) {
    return AudioProcessor::getParameter(parameterIndex);
}

String SineOperatorContentComponent::getParameterName(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterName(parameterIndex, maximumStringLength);
}

const String SineOperatorContentComponent::getParameterText(int parameterIndex) {
    return AudioProcessor::getParameterText(parameterIndex);
}

String SineOperatorContentComponent::getParameterText(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterText(parameterIndex, maximumStringLength);
}

int SineOperatorContentComponent::getParameterNumSteps(int parameterIndex) {
    return AudioProcessor::getParameterNumSteps(parameterIndex);
}

float SineOperatorContentComponent::getParameterDefaultValue(int parameterIndex) {
    return AudioProcessor::getParameterDefaultValue(parameterIndex);
}

String SineOperatorContentComponent::getParameterLabel(int index) const {
    return AudioProcessor::getParameterLabel(index);
}

bool SineOperatorContentComponent::isParameterOrientationInverted(int index) const {
    return AudioProcessor::isParameterOrientationInverted(index);
}

void SineOperatorContentComponent::setParameter(int parameterIndex, float newValue) {
}

bool SineOperatorContentComponent::isParameterAutomatable(int parameterIndex) const {
    return AudioProcessor::isParameterAutomatable(parameterIndex);
}

bool SineOperatorContentComponent::isMetaParameter(int parameterIndex) const {
    return AudioProcessor::isMetaParameter(parameterIndex);
}

void SineOperatorContentComponent::getCurrentProgramStateInformation(juce::MemoryBlock &destData) {
}

void SineOperatorContentComponent::setCurrentProgramStateInformation(const void *data,
                                                                  int sizeInBytes) {
}

void SineOperatorContentComponent::numChannelsChanged() {
}

void SineOperatorContentComponent::addListener(AudioProcessorListener *newListener) {
}

void SineOperatorContentComponent::removeListener(AudioProcessorListener *listenerToRemove) {
}

void SineOperatorContentComponent::setPlayHead(AudioPlayHead *newPlayHead) {
}
*/

//void SineOperatorContentComponent::processBlock(AudioBuffer<double> &buffer,
 //                                            MidiBuffer &midiMessages) {
//}

//void SineOperatorContentComponent::processBlockBypassed(AudioBuffer<double> &buffer,
 //                                                    MidiBuffer &midiMessages) {
//}


