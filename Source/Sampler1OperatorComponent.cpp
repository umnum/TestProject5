/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include <src/main/jni/BinaryData.h>
#include <src/main/jni/AppConfig.h>
#include "Sampler1OperatorComponent.h"
#include "Sampler1PluginEditor.h"
#include "MainComponent.h"


//==============================================================================
    Sampler1OperatorContentComponent::Sampler1OperatorContentComponent()
    : thread("audio file preview")
    {
    }

Sampler1OperatorContentComponent::Sampler1OperatorContentComponent(Image image, double freq)
    :   currentSampleRate(0.0),
        currentAngle(0.0),
        angleDelta(0.0),
        doubleClick(false),
        distance(0),
        pos(0),
        level(0.5),
        triggered(false),
        timer(0),
        thread("audio file preview")
    {
        this->image = image;
        this->freq = freq;
        const String base = getenv("EXTERNAL_STORAGE");
        const String path = "/Download";
        formatManager.registerBasicFormats();
        transportSource.addChangeListener(this);
        thread.startThread(3);
        deviceManager.initialise(2,2,0,true,String(),0);
        deviceManager.addAudioCallback(&audioSourcePlayer);
        audioSourcePlayer.setSource(&transportSource);
        soundFile = new File(base+path);
        Logger *log = Logger::getCurrentLogger();
        log->outputDebugString("Number of registered formats: "+String(formatManager.getNumKnownFormats()));
        log->outputDebugString("Wildcard formats: "+String(formatManager.getWildcardForAllFormats()));
        log->outputDebugString(soundFile->getFullPathName());
        if (soundFile->exists()) {
            log->outputDebugString(soundFile->getFullPathName() + " exists.");
            log->outputDebugString("There are " + String(soundFile->getNumberOfChildFiles(File::findFiles,"*.mp3")) + " music files in this directory.");
        }
        DirectoryIterator iter(*soundFile, true, "disconnect.wav");
        while(iter.next()) {
            File mp3File(iter.getFile());
            FileInputStream *inputStream = mp3File.createInputStream();
            log->outputDebugString(mp3File.getFileName());
            if (inputStream == nullptr)
                log->outputDebugString("Error: " + String(mp3File.getFileName()) + " input stream not created");
            else
                log->outputDebugString("SUCCESS! " + String(mp3File.getFileName()) + " input stream created");
            transportSource.stop();
            transportSource.setSource(nullptr);
            currentAudioFileSource = nullptr;
            AudioFormatReader *reader = formatManager.createReaderFor(inputStream);
            if (reader == nullptr)
                log->outputDebugString("Error: " + String(mp3File.getFileName()) + " format reader not created");
            else {
                log->outputDebugString(
                        "SUCCESS! " + String(mp3File.getFileName()) + " format reader created");
                log->outputDebugString("reader sampleRate is " + String(reader->sampleRate));
                fileBuffer.setSize(reader->numChannels, reader->lengthInSamples);
                log->outputDebugString("fileBuffer has " + String(fileBuffer.getNumChannels()) + " input channels");
                reader->read(&fileBuffer, 0, reader->lengthInSamples, 0, true, true);
                pos = 0;
                transportSource.setSource(currentAudioFileSource, 32768, &thread, reader->sampleRate);
                transportSource.setPosition(0);
                transportSource.start();
            }
        }

        //setAudioChannels(0,1);
    }

    Sampler1OperatorContentComponent::~Sampler1OperatorContentComponent() {
        //shutdownAudio();
    }

    void Sampler1OperatorContentComponent::paint(Graphics &g) {
        g.drawImageWithin(image, 0, 0, getWidth(), getHeight(),
                          RectanglePlacement::onlyReduceInSize, false);
    }

    void Sampler1OperatorContentComponent::resized() {
        // This is called when the Sampler1OperatorContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

//=======================================================================
//void Sampler1OperatorContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
//{
  //  currentSampleRate = sampleRate;
 //   updateAngleDelta();
//}

    void Sampler1OperatorContentComponent::updateAngleDelta()
    {
        const double cyclesPerSample = freq / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

    void Sampler1OperatorContentComponent::processBlock(AudioBuffer<float> &buffer,
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

        if (triggered) {
            const int numInputChannels = fileBuffer.getNumChannels();
            const int numOutputChannels = buffer.getNumChannels();

            int outputSamplesRemaining = buffer.getNumSamples();
            int outputSamplesOffset = 0;

            while (outputSamplesRemaining > 0) {
                if (!triggered)
                    break;
                int bufferSamplesRemaining = fileBuffer.getNumSamples() - pos;
                int samplesThisTime = jmin(outputSamplesRemaining, bufferSamplesRemaining);

                for (int channel = 0; channel < numOutputChannels; ++channel) {
                    buffer.copyFrom(channel, outputSamplesOffset, fileBuffer,
                                    channel % numInputChannels,
                                    pos, samplesThisTime);
                    buffer.applyGain(channel, outputSamplesOffset, samplesThisTime, level * 0.125f);
                }
                outputSamplesRemaining -= samplesThisTime;
                outputSamplesOffset += samplesThisTime;
                pos += samplesThisTime;
                if (pos == fileBuffer.getNumSamples()) {
                    pos = 0;
                }
            }
        }
    }

    void Sampler1OperatorContentComponent::initEnv(int envSize, int attackSize, int decaySize) {
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
    }

    float Sampler1OperatorContentComponent::envTick() {
        if (triggered) {
            pos++;
            return float(env[pos]);
        }
        else {
            pos = 0;
            return 0.0f;
        }
    }

//void Sampler1OperatorContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
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


    void Sampler1OperatorContentComponent::releaseResources()
    {
        pos = 0;
    }

//=======================================================================

    void Sampler1OperatorContentComponent::mouseDown(const MouseEvent &e) {
        myDragger.startDraggingComponent(this, e);
    }

    void Sampler1OperatorContentComponent::mouseDrag(const MouseEvent &e) {
        myDragger.dragComponent(this, e, nullptr);
        updateAngleDelta();
    }

    void Sampler1OperatorContentComponent::mouseDoubleClick(const MouseEvent &e) {
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

    void Sampler1OperatorContentComponent::sliderValueChanged(Slider *slider) {
    }

    bool Sampler1OperatorContentComponent::isClicked() {
        return doubleClick;
    }

    void Sampler1OperatorContentComponent::setClicked(bool doubleClick) {
        this->doubleClick = doubleClick;
    }

    bool Sampler1OperatorContentComponent::isMostRecentlyDoubleClicked() {
        return mostRecentlyDoubleClicked;
    }

    void Sampler1OperatorContentComponent::setMostRecentlyDoubleClicked(
            bool mostRecentlyDoubleClicked) {
        this->mostRecentlyDoubleClicked = mostRecentlyDoubleClicked;
    }

    float Sampler1OperatorContentComponent::getLevel() {
        return level;
    }

    void Sampler1OperatorContentComponent::setLevel(float level) {
        this->level = level;
    }

    double Sampler1OperatorContentComponent::getFreq() {
        return freq;
    }

    void Sampler1OperatorContentComponent::setFreq(double freq) {
        this->freq = freq;
    }

    const String Sampler1OperatorContentComponent::getName() const {
        return JucePlugin_Name;
    }

    bool Sampler1OperatorContentComponent::acceptsMidi() const {
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool Sampler1OperatorContentComponent::silenceInProducesSilenceOut() const {
        return false;
    }
    double Sampler1OperatorContentComponent::getTailLengthSeconds() const {
        return 0.0;
    }

    int Sampler1OperatorContentComponent::getNumPrograms() {
        return 1;
    }

    int Sampler1OperatorContentComponent::getCurrentProgram() {
        return 0;
    }

    void Sampler1OperatorContentComponent::setCurrentProgram(int index) {
    }

    const String Sampler1OperatorContentComponent::getProgramName(int index) {
        return String();
    }

    void Sampler1OperatorContentComponent::changeProgramName(int index, const String &newName) {
    }

    bool Sampler1OperatorContentComponent::hasEditor() const {
        return true;
    }

    AudioProcessorEditor* Sampler1OperatorContentComponent::createEditor() {
        return new TestProject5AudioSampler1ProcessorEditor (*this);
    }

    void Sampler1OperatorContentComponent::getStateInformation(MemoryBlock &destData) {
    }

    void Sampler1OperatorContentComponent::setStateInformation(const void *data, int sizeInBytes) {
    }

    /*AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
        return new Sampler1OperatorContentComponent();
    }*/

    bool Sampler1OperatorContentComponent::producesMidi() const {
        return false;
    }

    void Sampler1OperatorContentComponent::sliderDragStarted(Slider *slider) {
    }

    void Sampler1OperatorContentComponent::sliderDragEnded(Slider *slider) {
    }

    void Sampler1OperatorContentComponent::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {
        currentSampleRate = sampleRate;
        int envSize = int(currentSampleRate/10.0);
        int attackSize = int(envSize/8.0);
        int decaySize = attackSize;
        initEnv(envSize, attackSize, decaySize);
    }

    bool Sampler1OperatorContentComponent::setTriggered(bool triggered) {
        if (triggered && !this->triggered)
            timer = 100;
        if (!triggered)
            pos = 0;
        this->triggered = triggered;
    }

    void Sampler1OperatorContentComponent::setSustained(bool sustained) {
        this->sustained = sustained;
    }

    bool Sampler1OperatorContentComponent::isSustained() {
        return sustained;
    }

    void Sampler1OperatorContentComponent::hiResTimerCallback() {
        if(triggered); // <--- REMEMBER, there is a semicolon there
            //timer--;
        if (!timer)
            triggered = false;
    }

    void Sampler1OperatorContentComponent::changeListenerCallback(ChangeBroadcaster *source) {
    }

/*
void Sampler1OperatorContentComponent::processBlockBypassed(AudioBuffer<float> &buffer,
                                                     MidiBuffer &midiMessages) {
    AudioProcessor::processBlockBypassed(buffer, midiMessages);
}

bool Sampler1OperatorContentComponent::setPreferredBusArrangement(bool isInputBus, int busIndex,
                                                           const AudioChannelSet &preferredSet) {
    return AudioProcessor::setPreferredBusArrangement(isInputBus, busIndex, preferredSet);
}

bool Sampler1OperatorContentComponent::supportsDoublePrecisionProcessing() const {
    return AudioProcessor::supportsDoublePrecisionProcessing();
}

void Sampler1OperatorContentComponent::reset() {
    AudioProcessor::reset();
}

void Sampler1OperatorContentComponent::setNonRealtime(bool isNonRealtime) noexcept{
}

int Sampler1OperatorContentComponent::getNumParameters() {
    return AudioProcessor::getNumParameters();
}

const String Sampler1OperatorContentComponent::getParameterName(int parameterIndex) {
    return AudioProcessor::getParameterName(parameterIndex);
}

float Sampler1OperatorContentComponent::getParameter(int parameterIndex) {
    return AudioProcessor::getParameter(parameterIndex);
}

String Sampler1OperatorContentComponent::getParameterName(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterName(parameterIndex, maximumStringLength);
}

const String Sampler1OperatorContentComponent::getParameterText(int parameterIndex) {
    return AudioProcessor::getParameterText(parameterIndex);
}

String Sampler1OperatorContentComponent::getParameterText(int parameterIndex, int maximumStringLength) {
    return AudioProcessor::getParameterText(parameterIndex, maximumStringLength);
}

int Sampler1OperatorContentComponent::getParameterNumSteps(int parameterIndex) {
    return AudioProcessor::getParameterNumSteps(parameterIndex);
}

float Sampler1OperatorContentComponent::getParameterDefaultValue(int parameterIndex) {
    return AudioProcessor::getParameterDefaultValue(parameterIndex);
}

String Sampler1OperatorContentComponent::getParameterLabel(int index) const {
    return AudioProcessor::getParameterLabel(index);
}

bool Sampler1OperatorContentComponent::isParameterOrientationInverted(int index) const {
    return AudioProcessor::isParameterOrientationInverted(index);
}

void Sampler1OperatorContentComponent::setParameter(int parameterIndex, float newValue) {
}

bool Sampler1OperatorContentComponent::isParameterAutomatable(int parameterIndex) const {
    return AudioProcessor::isParameterAutomatable(parameterIndex);
}

bool Sampler1OperatorContentComponent::isMetaParameter(int parameterIndex) const {
    return AudioProcessor::isMetaParameter(parameterIndex);
}

void Sampler1OperatorContentComponent::getCurrentProgramStateInformation(juce::MemoryBlock &destData) {
}

void Sampler1OperatorContentComponent::setCurrentProgramStateInformation(const void *data,
                                                                  int sizeInBytes) {
}

void Sampler1OperatorContentComponent::numChannelsChanged() {
}

void Sampler1OperatorContentComponent::addListener(AudioProcessorListener *newListener) {
}

void Sampler1OperatorContentComponent::removeListener(AudioProcessorListener *listenerToRemove) {
}

void Sampler1OperatorContentComponent::setPlayHead(AudioPlayHead *newPlayHead) {
}
*/

//void Sampler1OperatorContentComponent::processBlock(AudioBuffer<double> &buffer,
 //                                            MidiBuffer &midiMessages) {
//}

//void Sampler1OperatorContentComponent::processBlockBypassed(AudioBuffer<double> &buffer,
 //                                                    MidiBuffer &midiMessages) {
//}


