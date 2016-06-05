/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/


#include <src/main/jni/BinaryData.h>
#include "MainComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
    //==============================================================================
    MainContentComponent::MainContentComponent()
    :   resetButton("stop"),
        fGraph(),
        radarRefresh(0),
        tremoloDistance(150.0)
    {
        fDeviceManager.initialise(2, 2, nullptr, true);
        fDeviceManager.addAudioCallback(&fPlayer);
        Reset();
        fPlayer.setProcessor(&fGraph);

        /* load image data */
        const char* imageName[7];
        int imageSize[7];
        imageName[0] = BinaryData::sine_png;
        imageSize[0] = BinaryData::sine_pngSize;
        imageName[1] = BinaryData::trem_png;
        imageSize[1] = BinaryData::trem_pngSize;
        imageName[2] = BinaryData::radar_png;
        imageSize[2] = BinaryData::radar_pngSize;
        imageName[3] = BinaryData::samp1_png;
        imageSize[3] = BinaryData::samp1_pngSize;
        imageName[4] = BinaryData::delay_png;
        imageSize[4] = BinaryData::delay_pngSize;
        imageName[5] = BinaryData::echo_png;
        imageSize[5] = BinaryData::echo_pngSize;
        imageName[6] = BinaryData::play_png;
        imageSize[6] = BinaryData::play_pngSize;

        /* initialize menu buttons */
        for (int i = 0; i < 7; ++i) {
            String buttonName;
            buttonName << "Button " << String(i);
            ImageButton *button = new ImageButton(buttonName);
            image.set(i, ImageCache::getFromMemory(imageName[i], imageSize[i]));
            button->setImages(false, true, true, image[i], 1.0f, Colour(0x0), Image(), 1.0f, Colour(0x0),
                              Image(), 1.0f, Colour(0x0));
            button->addListener(this);
            buttons.add(button);
            addAndMakeVisible(button);
        }


        resetButton.addListener(this);
        addAndMakeVisible(&resetButton);
        setSize (800, 600);
        // MainComponent timer triggers every 1 millisecond
        startTimer(1);
    }

    MainContentComponent::~MainContentComponent()
    {
    }

    /* remove all nodes connected to the audioprocessor graph and
     * create an input and output node for the main bus */
    void MainContentComponent::Reset()
    {
        Logger *log = Logger::getCurrentLogger();
        fGraph.clear();
        in = new AudioGraphIOProcessor(AudioGraphIOProcessor::audioInputNode);
        out = new AudioGraphIOProcessor(AudioGraphIOProcessor::audioOutputNode);
        const AudioChannelSet &channelTypes1 = AudioChannelSet::stereo();
        AudioProcessorBus *newBusIn = new AudioProcessorBus("input bus", channelTypes1);
        in->busArrangement.inputBuses.add(*newBusIn);
        log->outputDebugString("The size of op1 inputBuses = " + String(in->busArrangement.inputBuses.size()));
        const AudioChannelSet &channelTypes = AudioChannelSet::stereo();
        AudioProcessorBus *newBusOut = new AudioProcessorBus("input bus", channelTypes);
        out->busArrangement.inputBuses.add(*newBusOut);
        log->outputDebugString("The size of op2 inputBuses = " + String(out->busArrangement.inputBuses.size()));

        if(in->setPreferredBusArrangement(true,0,AudioChannelSet::stereo()))
            log->outputDebugString("Bus Arrangement set for in");
        if(out->setPreferredBusArrangement(true,0,AudioChannelSet::stereo()))
            log->outputDebugString("Bus Arrangement set for out");
        log->outputDebugString("in->getMainBusNumInputChannels() = " + String(in->getMainBusNumInputChannels()));
        log->outputDebugString("in->getMainBusNumOutputChannels() = " + String(in->getMainBusNumOutputChannels()));
        log->outputDebugString("out->getMainBusNumInputChannels() = " + String(out->getMainBusNumInputChannels()));
        log->outputDebugString("out->getMainBusNumOutputChannels() = " + String(out->getMainBusNumOutputChannels()));
        fInputNode = fGraph.addNode(in);
        fOutputNode = fGraph.addNode(out);
    }

    // initialize new operator and connect it to the input/output bus
    // returns true if the right connections were made
    bool MainContentComponent::Connect(component componentType, bool hasInput, bool hasOutput) {
        Logger *log = Logger::getCurrentLogger();
        Node *newNode = nullptr;
        switch (componentType) {
            case SINE : {
                SineOperatorContentComponent *newSineOperator = new SineOperatorContentComponent(
                        image[0], 220.0);
                newSineOperator->addMouseListener(this, true);
                sineOperators.add(newSineOperator);
                addAndMakeVisible(newSineOperator);
                //newSineOperator->setBoundsRelative(0.075, 0.825, 0.10, 0.10);
                newSineOperator->setBoundsRelative(0.030, 0.86, 0.10, 0.10);
                newSineOperator->addComponentListener(this);
                newSineOperator->startTimer(1);
                Slider *newSineVolSlider = new Slider();
                Slider *newSineFreqSlider = new Slider();
                newSineVolSlider->setBounds(500, 30, 300, 40);
                newSineVolSlider->setRange(0.0,1.0);
                newSineFreqSlider->setBounds(500, 70, 300, 40);
                newSineFreqSlider->setRange(50.0,1000.0);
                sineVolSlider.add(newSineVolSlider);
                addAndMakeVisible(newSineVolSlider);
                newSineVolSlider->setVisible(false);
                newSineVolSlider->addListener(this);
                sineFreqSlider.add(newSineFreqSlider);
                addAndMakeVisible(newSineFreqSlider);
                newSineFreqSlider->setVisible(false);
                newSineFreqSlider->addListener(this);
                newNode = fGraph.addNode(newSineOperator);
                const AudioChannelSet &channelTypes1 = AudioChannelSet::stereo();
                AudioProcessorBus *newBus = new AudioProcessorBus("input bus", channelTypes1);
                newSineOperator->busArrangement.inputBuses.add(*newBus);
                sineNodes.add(newNode);
                break;
            }
            case TREMOLO : {
                TremoloOperatorContentComponent *newTremoloOperator = new TremoloOperatorContentComponent(
                        image[1], buttons[1]->getX());
                newTremoloOperator->addMouseListener(this, true);
                tremoloOperators.add(newTremoloOperator);
                addAndMakeVisible(newTremoloOperator);
                //newTremoloOperator->setBoundsRelative(0.225, 0.825, 0.10, 0.10);
                newTremoloOperator->setBoundsRelative(0.15, 0.86, 0.10, 0.10);
                newTremoloOperator->addComponentListener(this);

                Slider *newTremoloIntensitySlider = new Slider();
                Slider *newTremoloFreqSlider = new Slider();
                newTremoloIntensitySlider->setBounds(500, 30, 300, 40);
                newTremoloIntensitySlider->setRange(0.0,1.0);
                newTremoloFreqSlider->setBounds(500, 70, 300, 40);
                newTremoloFreqSlider->setRange(0.0,100.0);
                tremoloIntensitySlider.add(newTremoloIntensitySlider);
                addAndMakeVisible(newTremoloIntensitySlider);
                newTremoloIntensitySlider->setVisible(false);
                newTremoloIntensitySlider->addListener(this);
                tremoloFreqSlider.add(newTremoloFreqSlider);
                addAndMakeVisible(newTremoloFreqSlider);
                newTremoloFreqSlider->setVisible(false);
                newTremoloFreqSlider->addListener(this);

                const AudioChannelSet &channelTypes1 = AudioChannelSet::stereo();
                AudioProcessorBus *newBus = new AudioProcessorBus("input bus", channelTypes1);
                newTremoloOperator->busArrangement.inputBuses.add(*newBus);
                if (newTremoloOperator->setPreferredBusArrangement(true, 0,
                                                                   AudioChannelSet::stereo()))
                    log->outputDebugString("Bus Arrangement set for new koperator");
                newNode = fGraph.addNode(newTremoloOperator);
                tremoloNodes.add(newNode);
                break;
            }
            case RADAR : {
                RadarTriggerComponent *newRadarOperator = new RadarTriggerComponent(
                        image[2], 1.0);
                newRadarOperator->addMouseListener(this, true);
                radarTriggers.add(newRadarOperator);
                addAndMakeVisible(newRadarOperator);
                //newRadarOperator->setBoundsRelative(0.375, 0.825, 0.10, 0.10);
                newRadarOperator->setBoundsRelative(0.27, 0.86, 0.10, 0.10);
                newRadarOperator->addComponentListener(this);
                newRadarOperator->startTimer(1);
                newRadarOperator->setRadarDistance(100);

                Slider *newRadarFreqSlider = new Slider();
                newRadarFreqSlider->setBounds(500, 30, 300, 40);
                newRadarFreqSlider->setRange(0.0,5.0);
                radarFreqSlider.add(newRadarFreqSlider);
                addAndMakeVisible(newRadarFreqSlider);
                newRadarFreqSlider->setVisible(false);
                newRadarFreqSlider->addListener(this);

                Slider *newRadarLengthSlider = new Slider();
                newRadarLengthSlider->setBounds(500, 70, 300, 40);
                newRadarLengthSlider->setRange(50,200);
                radarLengthSlider.add(newRadarLengthSlider);
                addAndMakeVisible(newRadarLengthSlider);
                newRadarLengthSlider->setVisible(false);
                newRadarLengthSlider->addListener(this);
                break;
            }
            case SAMP1 : {
                Sampler1OperatorContentComponent *newSamp1Operator = new Sampler1OperatorContentComponent(
                        image[3], 220.0);
                newSamp1Operator->addMouseListener(this, true);
                sampler1Operators.add(newSamp1Operator);
                addAndMakeVisible(newSamp1Operator);
                //newSamp1Operator->setBoundsRelative(0.525, 0.825, 0.10, 0.10);
                newSamp1Operator->setBoundsRelative(0.39, 0.86, 0.10, 0.10);
                newSamp1Operator->addComponentListener(this);
                newSamp1Operator->startTimer(1);
                Slider *newSamp1VolSlider = new Slider();
                newSamp1VolSlider->setBounds(500, 30, 300, 40);
                newSamp1VolSlider->setRange(0.0,1.0);
                sampler1VolSlider.add(newSamp1VolSlider);
                addAndMakeVisible(newSamp1VolSlider);
                newSamp1VolSlider->setVisible(false);
                newSamp1VolSlider->addListener(this);
                newNode = fGraph.addNode(newSamp1Operator);
                const AudioChannelSet &channelTypes1 = AudioChannelSet::stereo();
                AudioProcessorBus *newBus = new AudioProcessorBus("input bus", channelTypes1);
                newSamp1Operator->busArrangement.inputBuses.add(*newBus);
                samp1Nodes.add(newNode);
                break;
            }
            case DELAY : {
                DelayOperatorContentComponent *newDelayOperator = new DelayOperatorContentComponent(
                        image[4], buttons[1]->getX());
                newDelayOperator->addMouseListener(this, true);
                delayOperators.add(newDelayOperator);
                addAndMakeVisible(newDelayOperator);
                //newDelayOperator->setBoundsRelative(0.675, 0.825, 0.10, 0.10);
                newDelayOperator->setBoundsRelative(0.51, 0.86, 0.10, 0.10);
                newDelayOperator->addComponentListener(this);

                Slider *newDelaySlider = new Slider();
                newDelaySlider->setBounds(500, 30, 300, 40);
                newDelaySlider->setRange(0.0,1.0);
                delaySlider.add(newDelaySlider);
                addAndMakeVisible(newDelaySlider);
                newDelaySlider->setVisible(false);
                newDelaySlider->addListener(this);

                const AudioChannelSet &channelTypes1 = AudioChannelSet::stereo();
                AudioProcessorBus *newBus = new AudioProcessorBus("input bus", channelTypes1);
                newDelayOperator->busArrangement.inputBuses.add(*newBus);
                if (newDelayOperator->setPreferredBusArrangement(true, 0,
                                                                   AudioChannelSet::stereo()))
                    log->outputDebugString("Bus Arrangement set for new koperator");
                newNode = fGraph.addNode(newDelayOperator);
                delayNodes.add(newNode);
                break;
            }
            case ECHO : {
                EchoOperatorContentComponent *newEchoOperator = new EchoOperatorContentComponent(
                        image[5], buttons[1]->getX());
                newEchoOperator->addMouseListener(this, true);
                echoOperators.add(newEchoOperator);
                addAndMakeVisible(newEchoOperator);
                //newEchoOperator->setBoundsRelative(0.825, 0.825, 0.10, 0.10);
                newEchoOperator->setBoundsRelative(0.63, 0.86, 0.10, 0.10);
                newEchoOperator->addComponentListener(this);

                Slider *newEchoIntensitySlider = new Slider();
                newEchoIntensitySlider->setBounds(500, 30, 300, 40);
                newEchoIntensitySlider->setRange(0.0,1.0);
                echoIntensitySlider.add(newEchoIntensitySlider);
                addAndMakeVisible(newEchoIntensitySlider);
                newEchoIntensitySlider->setVisible(false);
                newEchoIntensitySlider->addListener(this);

                Slider *newEchoDelaySlider = new Slider();
                newEchoDelaySlider->setBounds(500, 70, 300, 40);
                newEchoDelaySlider->setRange(0.0,1.0);
                echoDelaySlider.add(newEchoDelaySlider);
                addAndMakeVisible(newEchoDelaySlider);
                newEchoDelaySlider->setVisible(false);
                newEchoDelaySlider->addListener(this);

                const AudioChannelSet &channelTypes1 = AudioChannelSet::stereo();
                AudioProcessorBus *newBus = new AudioProcessorBus("input bus", channelTypes1);
                newEchoOperator->busArrangement.inputBuses.add(*newBus);
                if (newEchoOperator->setPreferredBusArrangement(true, 0,
                                                                 AudioChannelSet::stereo()))
                    log->outputDebugString("Bus Arrangement set for new koperator");
                newNode = fGraph.addNode(newEchoOperator);
                echoNodes.add(newNode);
                break;
            }
            case PLAY : {
                PlayComponent *newPlayOperator = new PlayComponent(
                        image[6]);
                newPlayOperator->addMouseListener(this, true);
                playOperators.add(newPlayOperator);
                addAndMakeVisible(newPlayOperator);
                //newRadarOperator->setBoundsRelative(0.375, 0.825, 0.10, 0.10);
                newPlayOperator->setBoundsRelative(0.75, 0.86, 0.10, 0.10);
                newPlayOperator->addComponentListener(this);
                break;
            }
            default :
                return false;
        }
        if (hasInput) {
            if (fGraph.addConnection(fInputNode->nodeId, 0, newNode->nodeId, 0)) {
                if (fGraph.addConnection(fInputNode->nodeId, 1, newNode->nodeId, 1)) {
                    log->outputDebugString("made input connection");
                }
                else {
                    log->outputDebugString("no input connection made on channel 2");
                    return false;
                }
            }
            else {
                log->outputDebugString("no input connection made on channel 1");
                return false;
            }
        }
        if (hasOutput){
            if (fGraph.addConnection(newNode->nodeId, 0, fOutputNode->nodeId, 0)) {
                if (fGraph.addConnection(newNode->nodeId, 1, fOutputNode->nodeId, 1)) {
                    log->outputDebugString("made output connection");
                }
                else {
                    log->outputDebugString("no output connection made on channel 2");
                    return false;
                }
            }
            else {
                log->outputDebugString("no output connection made on channel 1");
                return false;
            }
        }
        return true;
    }

    //=======================================================================
    void MainContentComponent::paint(Graphics& g)
    {
        // You can add your drawing code here!
        Logger *log = Logger::getCurrentLogger();
        g.fillAll(Colours::darkblue);
        g.setColour(Colours::red);
        /* draw cable connections from every connected sine operator to tremolo operator */
        for (int i = 0; i < sineOperators.size(); ++i) {
            for (int j = 0; j < tremoloOperators.size(); ++j) {
                if (fGraph.isConnected(sineNodes[i]->nodeId,tremoloNodes[j]->nodeId)) {
                    g.drawLine(sineOperators[i]->getX()+sineOperators[i]->getWidth()/2,sineOperators[i]->getY()+sineOperators[i]->getHeight()/2,
                               tremoloOperators[j]->getX()+tremoloOperators[j]->getWidth()/2, tremoloOperators[j]->getY()+tremoloOperators[j]->getHeight()/2, 4);
                }
            }
            for (int j = 0; j < delayOperators.size(); ++j) {
                if (fGraph.isConnected(sineNodes[i]->nodeId,delayNodes[j]->nodeId)) {
                    g.drawLine(sineOperators[i]->getX()+sineOperators[i]->getWidth()/2,sineOperators[i]->getY()+sineOperators[i]->getHeight()/2,
                               delayOperators[j]->getX()+delayOperators[j]->getWidth()/2, delayOperators[j]->getY()+delayOperators[j]->getHeight()/2, 4);
                }
            }
            for (int j = 0; j < echoOperators.size(); ++j) {
                if (fGraph.isConnected(sineNodes[i]->nodeId,echoNodes[j]->nodeId)) {
                    g.drawLine(sineOperators[i]->getX()+sineOperators[i]->getWidth()/2,sineOperators[i]->getY()+sineOperators[i]->getHeight()/2,
                               echoOperators[j]->getX()+echoOperators[j]->getWidth()/2, echoOperators[j]->getY()+echoOperators[j]->getHeight()/2, 4);
                }
            }
        }
        /* draw cable connections from every play operator to sine operator within connecting distance */
        for (int i = 0; i < playOperators.size(); ++i){
            for (int j = 0; j < sineOperators.size(); ++j) {
                if (playOperators[i]->isWithinTriggerDistance(j)) {
                    g.drawLine(playOperators[i]->getX()+playOperators[i]->getWidth()/2,playOperators[i]->getY()+playOperators[i]->getHeight()/2,
                               sineOperators[j]->getX()+sineOperators[j]->getWidth()/2, sineOperators[j]->getY()+sineOperators[j]->getHeight()/2, 4);
                }
            }
            for (int j = 0; j < sampler1Operators.size(); ++j) {
                if (playOperators[i]->sampler1IsWithinTriggerDistance(j)) {
                    g.drawLine(playOperators[i]->getX()+playOperators[i]->getWidth()/2,playOperators[i]->getY()+playOperators[i]->getHeight()/2,
                               sampler1Operators[j]->getX()+sampler1Operators[j]->getWidth()/2, sampler1Operators[j]->getY()+sampler1Operators[j]->getHeight()/2, 4);
                }
            }
        }
        /* draw cable connections from every connected samp1 operator to tremolo operator */
        for (int i = 0; i < sampler1Operators.size(); ++i) {
            for (int j = 0; j < tremoloOperators.size(); ++j) {
                if (fGraph.isConnected(samp1Nodes[i]->nodeId,tremoloNodes[j]->nodeId)) {
                    g.drawLine(sampler1Operators[i]->getX()+sampler1Operators[i]->getWidth()/2,sampler1Operators[i]->getY()+sampler1Operators[i]->getHeight()/2,
                               tremoloOperators[j]->getX()+tremoloOperators[j]->getWidth()/2, tremoloOperators[j]->getY()+tremoloOperators[j]->getHeight()/2, 4);
                }
            }
            for (int j = 0; j < delayOperators.size(); ++j) {
                if (fGraph.isConnected(samp1Nodes[i]->nodeId,delayNodes[j]->nodeId)) {
                    g.drawLine(sampler1Operators[i]->getX()+sampler1Operators[i]->getWidth()/2,sampler1Operators[i]->getY()+sampler1Operators[i]->getHeight()/2,
                               delayOperators[j]->getX()+delayOperators[j]->getWidth()/2, delayOperators[j]->getY()+delayOperators[j]->getHeight()/2, 4);
                }
            }
            for (int j = 0; j < echoOperators.size(); ++j) {
                if (fGraph.isConnected(samp1Nodes[i]->nodeId,echoNodes[j]->nodeId)) {
                    g.drawLine(sampler1Operators[i]->getX()+sampler1Operators[i]->getWidth()/2,sampler1Operators[i]->getY()+sampler1Operators[i]->getHeight()/2,
                               echoOperators[j]->getX()+echoOperators[j]->getWidth()/2, echoOperators[j]->getY()+echoOperators[j]->getHeight()/2, 4);
                }
            }
        }
        /* draw the spinning radar animation for every radar trigger object */
        for (int i = 0; i < radarTriggers.size(); ++i) {
            g.drawLine(radarTriggers[i]->getX()+radarTriggers[i]->getWidth()*0.5f,radarTriggers[i]->getY()+radarTriggers[i]->getHeight()*0.5f,
                       (float) (radarTriggers[i]->getX()+radarTriggers[i]->getWidth()*0.5+radarTriggers[i]->getRadarDistance()*std::cos(radarTriggers[i]->getTheta())),
                       (float) (radarTriggers[i]->getY()+radarTriggers[i]->getHeight()*0.5+radarTriggers[i]->getRadarDistance()*std::sin(radarTriggers[i]->getTheta())),4);
        }
    }

    void MainContentComponent::resized()
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        for (int i = 0; i < buttons.size(); ++i) {
            //buttons[i]->setBoundsRelative(0.05 + i*.15, 0.80, 0.15, 0.15);
            buttons[i]->setBoundsRelative(0.02 + i*.12, 0.85, 0.12, 0.12);
        }
        resetButton.setBoundsRelative(0.02, 0.02, 0.08, 0.04);
        for (int i = 0; i < sineOperators.size(); ++i) {
            sineVolSlider[i]->setBoundsRelative(0.05, 0.10, 0.2, 0.1);
            sineFreqSlider[i]->setBoundsRelative(0.05, 0.15, 0.2, 0.1);
        }
    }

    void MainContentComponent::sliderValueChanged(Slider *slider) {
        for (int i = 0; i < sineOperators.size(); ++i){
            if (slider == sineVolSlider[i]){
                sineOperators[i]->setLevel(sineVolSlider[i]->getValue());
                return;
            }
            if (slider == sineFreqSlider[i]){
                sineOperators[i]->setFreq(sineFreqSlider[i]->getValue());
                sineOperators[i]->updateAngleDelta();
                return;
            }
        }
        for (int i = 0; i < tremoloOperators.size(); ++i){
            if (slider == tremoloIntensitySlider[i]){
                tremoloOperators[i]->setLevel(tremoloIntensitySlider[i]->getValue());
                return;
            }
            if (slider == tremoloFreqSlider[i]){
                tremoloOperators[i]->setFreq(tremoloFreqSlider[i]->getValue());
                tremoloOperators[i]->updateAngleDelta();
                return;
            }
        }
        for (int i = 0; i < radarTriggers.size(); ++i){
            if (slider == radarFreqSlider[i]){
                radarTriggers[i]->setFreq(radarFreqSlider[i]->getValue());
                radarTriggers[i]->updateAngleDelta();
                return;
            }
            if (slider == radarLengthSlider[i]){
                radarTriggers[i]->setRadarDistance(radarLengthSlider[i]->getValue());
                componentMovedOrResized(*radarTriggers[i],true, false);
                return;
            }
        }
        for (int i = 0; i < sampler1Operators.size(); ++i){
            if (slider == sampler1VolSlider[i]){
                sampler1Operators[i]->setLevel(sampler1VolSlider[i]->getValue());
                return;
            }
        }
        for (int i = 0; i < delayOperators.size(); ++i){
            if (slider == delaySlider[i]){
                delayOperators[i]->setDelay(delaySlider[i]->getValue());
                return;
            }
        }
        for (int i = 0; i < echoOperators.size(); ++i){
            if (slider == echoIntensitySlider[i]){
                echoOperators[i]->setEchoIntensity(echoIntensitySlider[i]->getValue());
                return;
            }
            if (slider == echoDelaySlider[i]){
                echoOperators[i]->setEchoDelay(echoDelaySlider[i]->getValue());
                return;
            }
        }
    }

    void MainContentComponent::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {
        Logger *log = Logger::getCurrentLogger();
        log->outputDebugString("prepareToPlay() started in the main component class");
    }

    /* create a new operator corresponding to the button clicked in the menu sidebar */
    void MainContentComponent::buttonClicked(Button *button) {
        Logger *log = Logger::getCurrentLogger();

        /* reset button clicked */
        if (button == &resetButton) {
            for (int i = 0; i < sineOperators.size(); ++i) {
                for (int j = 0; j < tremoloOperators.size(); ++j) {
                    fGraph.removeConnection(sineNodes[i]->nodeId,0,tremoloNodes[j]->nodeId,0);
                    fGraph.removeConnection(sineNodes[i]->nodeId,1,tremoloNodes[j]->nodeId,1);
                }
                sineVolSlider[i]->removeListener(this);
                sineVolSlider[i]->setVisible(false);
                sineFreqSlider[i]->removeListener(this);
                sineFreqSlider[i]->setVisible(false);
                sineOperators[i]->suspendProcessing(true);
                //sineOperators[i]->releaseResources();
                sineOperators[i]->removeMouseListener(this);
                sineOperators[i]->removeComponentListener(this);
                sineOperators[i]->stopTimer();
                sineOperators[i]->busArrangement.inputBuses.clear();
                if (i == sineOperators.size() - 1) {
                    sineNodes.clear();
                    sineVolSlider.clear();
                    sineFreqSlider.clear();
                    sineOperators.clear();
                }
            }
            for (int i = 0; i < playOperators.size(); ++i) {
                playOperators[i]->setVisible(false);
            }
            for (int i = 0; i < playOperators.size(); ++i) {
                playOperators.remove(0,true);
            }
            for (int i = 0; i < tremoloOperators.size(); ++i) {
                tremoloOperators[i]->suspendProcessing(true);
                tremoloOperators[i]->releaseResources();
                tremoloNodes.remove(0,false);
                tremoloOperators.remove(0,false);
            }
            for (int i = 0; i < radarTriggers.size(); ++i) {
                radarFreqSlider[i]->removeListener(this);
                radarFreqSlider[i]->setVisible(false);
                radarLengthSlider[i]->removeListener(this);
                radarLengthSlider[i]->setVisible(false);
                radarTriggers[i]->removeMouseListener(this);
                radarTriggers[i]->removeComponentListener(this);
                radarTriggers[i]->stopTimer();
                if (i == radarTriggers.size()-1) {
                    radarFreqSlider.clear();
                    radarLengthSlider.clear();
                    radarTriggers.clear();
                }
            }
            fGraph.clear();
            fGraph.reset();
            Reset();
            /*
            for (int i = 0; i < sineOperators.size(); ++i) {
            }
            for (int i = 0; i < tremoloOperators.size(); ++i) {
            }
            fGraph.releaseResources();
             */
        } else {
            for (int i = 0; i < buttons.size(); ++i) {

                /* sine operator button was clicked */
                if (button == buttons[i] && i == 0) {
                    Connect(SINE, true, true);
                    break;
                }

                /* tremolo operator button was clicked */
                if (button == buttons[i] && i == 1) {
                    Connect(TREMOLO, false, true);
                    break;
                }

                /* radar operator button was clicked */
                if (button == buttons[i] && i == 2) {
                    Connect(RADAR, false, false);
                    break;
                }

                /* samp1 operator button was clicked */
                if (button == buttons[i] && i == 3) {
                    Connect(SAMP1, true, true);
                    break;
                }

                /*  delay operator button was clicked */
                if (button == buttons[i] && i == 4) {
                    Connect(DELAY, false, true);
                    break;
                }

                /*  echo operator button was clicked */
                if (button == buttons[i] && i == 5) {
                    Connect(ECHO, false, true);
                    break;
                }

                /*  play operator button was clicked */
                if (button == buttons[i] && i == 6) {
                    Connect(PLAY, false, false);
                    break;
                }
            }
        }
        for (int i = 0; i < sineOperators.size(); ++i) {
            log->outputDebugString("sineOperator " + String(i));
            log->outputDebugString(String(getX()));
        }
        for (int i = 0; i < tremoloOperators.size(); ++i) {
            log->outputDebugString("tremoloOperator " + String(i));
            log->outputDebugString(String(getX()));
        }

    }

    void MainContentComponent::componentMovedOrResized(Component &component, bool wasMoved,
                                                       bool wasResized) {
        Logger *log = Logger::getCurrentLogger();
        double a,b,c,theta,minDistance = -1.0f;
        int min = -1, prevMin=-1;

        if (wasMoved) { // an operator was moved

            /* check to see if a sine operator was moved */
            for (int i = 0; i < sineOperators.size(); ++i) {
                if (&component == sineOperators[i]) { // one of the sine operators was moved
                    // bring the current moved operator to the front
                    sineOperators[i]->toFront(true);
                    for (int j = 0; j < radarTriggers.size(); ++j) {
                        componentMovedOrResized(*radarTriggers[j], true, false);
                    }
                    for (int j = 0; j < playOperators.size(); ++j) {
                        componentMovedOrResized(*playOperators[j], true, false);
                    }
                    for (int j = 0; j < tremoloOperators.size(); ++j) {
                        a=sineOperators[i]->getX()+sineOperators[i]->getWidth()*0.5-(tremoloOperators[j]->getX()+tremoloOperators[j]->getWidth()*0.5);
                        b=sineOperators[i]->getY()+sineOperators[i]->getHeight()*0.5-(tremoloOperators[j]->getY()+tremoloOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        if (c < tremoloDistance) {
                            tremoloOperators[j]->repaint();
                            a *= -1;
                            tremoloOperators[j]->toBehind(sineOperators[i]);
                            if (fGraph.isConnected(sineNodes[i]->nodeId,tremoloNodes[j]->nodeId))
                                prevMin = j;
                            if (min < 0) {
                                min = j;
                                minDistance = c;
                            } else if (c < minDistance) {
                                minDistance = c;
                                min = j;
                            }
                        }
                        else {
                            if (fGraph.isConnected(sineNodes[i]->nodeId,tremoloNodes[j]->nodeId))
                                if (fGraph.addConnection(sineNodes[i]->nodeId,0,fOutputNode->nodeId,0))
                                    if (fGraph.addConnection(sineNodes[i]->nodeId,1,fOutputNode->nodeId,1))
                                        if (fGraph.removeConnection(sineNodes[i]->nodeId,0,tremoloNodes[j]->nodeId,0))
                                            if (fGraph.removeConnection(sineNodes[i]->nodeId,1,tremoloNodes[j]->nodeId,1)) {
                                                componentMovedOrResized(*tremoloOperators[j], true, false);
                                                log->outputDebugString("disconnection successful");
                                                //sineOperators[i]->setTriggered(false);
                                            }
                        }
                    }
                    if (min!=prevMin && prevMin >= 0)
                        if(fGraph.removeConnection(sineNodes[i]->nodeId,0,tremoloNodes[prevMin]->nodeId,0))
                            if(fGraph.removeConnection(sineNodes[i]->nodeId,1,tremoloNodes[prevMin]->nodeId,1)) {
                                log->outputDebugString("removed previous connection");
                                //sineOperators[i]->setTriggered(false);
                            }
                    if (min >= 0) {
                        if (!fGraph.isConnected(sineNodes[i]->nodeId, tremoloNodes[min]->nodeId))
                            if (fGraph.addConnection(sineNodes[i]->nodeId, 0, tremoloNodes[min]->nodeId, 0))
                                if (fGraph.addConnection(sineNodes[i]->nodeId, 1, tremoloNodes[min]->nodeId, 1))
                                    if (fGraph.removeConnection(sineNodes[i]->nodeId, 0, fOutputNode->nodeId, 0))
                                        if (fGraph.removeConnection(sineNodes[i]->nodeId, 1, fOutputNode->nodeId, 1))
                                            log->outputDebugString("connection successful");
                        //sineOperators[i]->setTriggered(true);
                    }
                    minDistance = -1.0f;
                    min = -1;
                    prevMin=-1;
                    for (int j = 0; j < delayOperators.size(); ++j) {
                        a=sineOperators[i]->getX()+sineOperators[i]->getWidth()*0.5-(delayOperators[j]->getX()+delayOperators[j]->getWidth()*0.5);
                        b=sineOperators[i]->getY()+sineOperators[i]->getHeight()*0.5-(delayOperators[j]->getY()+delayOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        if (c < tremoloDistance) {
                            delayOperators[j]->repaint();
                            a *= -1;
                            delayOperators[j]->toBehind(sineOperators[i]);
                            if (fGraph.isConnected(sineNodes[i]->nodeId,delayNodes[j]->nodeId))
                                prevMin = j;
                            if (min < 0) {
                                min = j;
                                minDistance = c;
                            } else if (c < minDistance) {
                                minDistance = c;
                                min = j;
                            }
                        }
                        else {
                            if (fGraph.isConnected(sineNodes[i]->nodeId,delayNodes[j]->nodeId))
                            if (fGraph.addConnection(sineNodes[i]->nodeId,0,fOutputNode->nodeId,0))
                            if (fGraph.addConnection(sineNodes[i]->nodeId,1,fOutputNode->nodeId,1))
                            if (fGraph.removeConnection(sineNodes[i]->nodeId,0,delayNodes[j]->nodeId,0))
                            if (fGraph.removeConnection(sineNodes[i]->nodeId,1,delayNodes[j]->nodeId,1)) {
                                //TODO this could be suspicous
                                componentMovedOrResized(*delayOperators[j], true, false);
                                log->outputDebugString("disconnection successful");
                                //sineOperators[i]->setTriggered(false);
                            }
                        }
                    }
                    if (min!=prevMin && prevMin >= 0)
                    if(fGraph.removeConnection(sineNodes[i]->nodeId,0,delayNodes[prevMin]->nodeId,0))
                    if(fGraph.removeConnection(sineNodes[i]->nodeId,1,delayNodes[prevMin]->nodeId,1)) {
                        log->outputDebugString("removed previous connection");
                        //sineOperators[i]->setTriggered(false);
                    }
                    if (min >= 0) {
                        if (!fGraph.isConnected(sineNodes[i]->nodeId, delayNodes[min]->nodeId))
                        if (fGraph.addConnection(sineNodes[i]->nodeId, 0, delayNodes[min]->nodeId, 0))
                        if (fGraph.addConnection(sineNodes[i]->nodeId, 1, delayNodes[min]->nodeId, 1))
                        if (fGraph.removeConnection(sineNodes[i]->nodeId, 0, fOutputNode->nodeId, 0))
                        if (fGraph.removeConnection(sineNodes[i]->nodeId, 1, fOutputNode->nodeId, 1))
                            log->outputDebugString("connection successful");
                        //sineOperators[i]->setTriggered(true);
                    }
                    minDistance = -1.0f;
                    min = -1;
                    prevMin=-1;
                    for (int j = 0; j < echoOperators.size(); ++j) {
                        a=sineOperators[i]->getX()+sineOperators[i]->getWidth()*0.5-(echoOperators[j]->getX()+echoOperators[j]->getWidth()*0.5);
                        b=sineOperators[i]->getY()+sineOperators[i]->getHeight()*0.5-(echoOperators[j]->getY()+echoOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        if (c < tremoloDistance) {
                            echoOperators[j]->repaint();
                            a *= -1;
                            echoOperators[j]->toBehind(sineOperators[i]);
                            if (fGraph.isConnected(sineNodes[i]->nodeId,echoNodes[j]->nodeId))
                                prevMin = j;
                            if (min < 0) {
                                min = j;
                                minDistance = c;
                            } else if (c < minDistance) {
                                minDistance = c;
                                min = j;
                            }
                        }
                        else {
                            if (fGraph.isConnected(sineNodes[i]->nodeId,echoNodes[j]->nodeId))
                            if (fGraph.addConnection(sineNodes[i]->nodeId,0,fOutputNode->nodeId,0))
                            if (fGraph.addConnection(sineNodes[i]->nodeId,1,fOutputNode->nodeId,1))
                            if (fGraph.removeConnection(sineNodes[i]->nodeId,0,echoNodes[j]->nodeId,0))
                            if (fGraph.removeConnection(sineNodes[i]->nodeId,1,echoNodes[j]->nodeId,1)) {
                                //TODO this could be suspicous
                                componentMovedOrResized(*echoOperators[j], true, false);
                                log->outputDebugString("disconnection successful");
                                //sineOperators[i]->setTriggered(false);
                            }
                        }
                    }
                    if (min!=prevMin && prevMin >= 0)
                    if(fGraph.removeConnection(sineNodes[i]->nodeId,0,echoNodes[prevMin]->nodeId,0))
                    if(fGraph.removeConnection(sineNodes[i]->nodeId,1,echoNodes[prevMin]->nodeId,1)) {
                        log->outputDebugString("removed previous connection");
                        //sineOperators[i]->setTriggered(false);
                    }
                    if (min >= 0) {
                        if (!fGraph.isConnected(sineNodes[i]->nodeId, echoNodes[min]->nodeId))
                        if (fGraph.addConnection(sineNodes[i]->nodeId, 0, echoNodes[min]->nodeId, 0))
                        if (fGraph.addConnection(sineNodes[i]->nodeId, 1, echoNodes[min]->nodeId, 1))
                        if (fGraph.removeConnection(sineNodes[i]->nodeId, 0, fOutputNode->nodeId, 0))
                        if (fGraph.removeConnection(sineNodes[i]->nodeId, 1, fOutputNode->nodeId, 1))
                            log->outputDebugString("connection successful");
                        //sineOperators[i]->setTriggered(true);
                    }
                    return;
                }
            }
            for (int i = 0; i < tremoloOperators.size(); ++i) {
                if (&component == tremoloOperators[i]) {
                    tremoloOperators[i]->toFront(true);
                    for (int j = 0; j < sineOperators.size(); ++j) {
                        a=tremoloOperators[i]->getX()+tremoloOperators[i]->getWidth()*0.5-(sineOperators[j]->getX()+sineOperators[j]->getWidth()*0.5);
                        b=tremoloOperators[i]->getY()+tremoloOperators[i]->getHeight()*0.5-(sineOperators[j]->getY()+sineOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        if (c < tremoloDistance) {
                            componentMovedOrResized(*sineOperators[j], true, false);
                            sineOperators[j]->toBehind(tremoloOperators[i]);
                        }
                        else {
                            if (fGraph.isConnected(sineNodes[j]->nodeId,tremoloNodes[i]->nodeId))
                                if (fGraph.addConnection(sineNodes[j]->nodeId,0,fOutputNode->nodeId,0))
                                    if (fGraph.addConnection(sineNodes[j]->nodeId,1,fOutputNode->nodeId,1))
                                        if (fGraph.removeConnection(sineNodes[j]->nodeId,0,tremoloNodes[i]->nodeId,0))
                                            if (fGraph.removeConnection(sineNodes[j]->nodeId,1,tremoloNodes[i]->nodeId,1)) {
                                                //repaint();
                                                //sineOperators[j]->setTriggered(false);
                                                componentMovedOrResized(*sineOperators[j], true, false);
                                                log->outputDebugString("disconnection successful");
                                            }
                        }
                    }
                    for (int j = 0; j < sampler1Operators.size(); ++j) {
                        a=tremoloOperators[i]->getX()+tremoloOperators[i]->getWidth()*0.5-(sampler1Operators[j]->getX()+sampler1Operators[j]->getWidth()*0.5);
                        b=tremoloOperators[i]->getY()+tremoloOperators[i]->getHeight()*0.5-(sampler1Operators[j]->getY()+sampler1Operators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        if (c < tremoloDistance) {
                            componentMovedOrResized(*sampler1Operators[j], true, false);
                            sampler1Operators[j]->toBehind(tremoloOperators[i]);
                        }
                        else {
                            if (fGraph.isConnected(samp1Nodes[j]->nodeId,tremoloNodes[i]->nodeId)) {
                                fGraph.addConnection(samp1Nodes[j]->nodeId, 0, fOutputNode->nodeId,
                                                     0);
                                fGraph.addConnection(samp1Nodes[j]->nodeId, 1, fOutputNode->nodeId,
                                                     1);
                                if (fGraph.removeConnection(samp1Nodes[j]->nodeId, 0,
                                                            tremoloNodes[i]->nodeId,
                                                            0)) if (fGraph.removeConnection(
                                        samp1Nodes[j]->nodeId, 1, tremoloNodes[i]->nodeId, 1)) {
                                    //repaint();
                                    //sineOperators[j]->setTriggered(false);
                                    componentMovedOrResized(*sampler1Operators[j], true, false);
                                    log->outputDebugString("disconnection successful");
                                }
                            }
                        }
                    }
                    return;
                }
            }
            for (int i = 0; i < radarTriggers.size(); ++i){
                if (&component == radarTriggers[i]) {
                    radarTriggers[i]->toFront(true);
                    for (int j = 0; j < sineOperators.size(); ++j) {
                        a=radarTriggers[i]->getX()+radarTriggers[i]->getWidth()*0.5f-(sineOperators[j]->getX()+sineOperators[j]->getWidth()*0.5f);
                        b=radarTriggers[i]->getY()+radarTriggers[i]->getHeight()*0.5f-(sineOperators[j]->getY()+sineOperators[j]->getHeight()*0.5f);
                        b = -b;
                        c = std::sqrt(a*a+b*b);
                        if (c < radarTriggers[i]->getRadarDistance()) {
                            radarTriggers[i]->withinTriggerDistance(j,true);
                            theta = std::atan(b/a);
                            if (a>0) {
                                theta += double_Pi;
                            }
                            else if (b>0)
                                theta += 2*double_Pi;
                            theta = 2*double_Pi-theta;
                            radarTriggers[i]->setAngleBetween(j, theta);
                            //componentMovedOrResized(*sineOperators[j], true, false);
                            sineOperators[j]->toBehind(radarTriggers[i]);
                        }
                        else
                            radarTriggers[i]->withinTriggerDistance(j,false);
                    }
                }
            }
            for (int i = 0; i < playOperators.size(); ++i){
                if (&component == playOperators[i]) {
                    playOperators[i]->toFront(true);
                    for (int j = 0; j < sineOperators.size(); ++j) {
                        a=playOperators[i]->getX()+playOperators[i]->getWidth()*0.5f-(sineOperators[j]->getX()+sineOperators[j]->getWidth()*0.5f);
                        b=playOperators[i]->getY()+playOperators[i]->getHeight()*0.5f-(sineOperators[j]->getY()+sineOperators[j]->getHeight()*0.5f);
                        c = std::sqrt(a*a+b*b);
                        //TODO replace tremoloDistance with something like playDistance, or distance
                        if (c < tremoloDistance) {
                            playOperators[i]->withinTriggerDistance(j,true);
                            sineOperators[j]->setSustained(true);
                            sineOperators[j]->setTriggered(true);
                            //componentMovedOrResized(*sineOperators[j], true, false);
                            sineOperators[j]->toBehind(playOperators[i]);
                            playOperators[i]->repaint();
                            sineOperators[j]->repaint();
                        }
                        else {
                            sineOperators[j]->setSustained(false);
                            playOperators[i]->withinTriggerDistance(j,false);
                            playOperators[i]->repaint();
                            sineOperators[j]->repaint();
                        }
                    }
                }
            }
            for (int i = 0; i < sampler1Operators.size(); ++i) {
                if (&component == sampler1Operators[i]) { // one of the sine operators was moved
                    // bring the current moved operator to the front
                    sampler1Operators[i]->toFront(true);
                    /*
                    for (int j = 0; j < radarTriggers.size(); ++j) {
                        componentMovedOrResized(*radarTriggers[j], true, false);
                    }
                    */
                    for (int j = 0; j < playOperators.size(); ++j) {
                        componentMovedOrResized(*playOperators[j], true, false);
                    }
                    for (int j = 0; j < tremoloOperators.size(); ++j) {
                        a=sampler1Operators[i]->getX()+sampler1Operators[i]->getWidth()*0.5-(tremoloOperators[j]->getX()+tremoloOperators[j]->getWidth()*0.5);
                        b=sampler1Operators[i]->getY()+sampler1Operators[i]->getHeight()*0.5-(tremoloOperators[j]->getY()+tremoloOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        if (c < tremoloDistance) {
                            tremoloOperators[j]->repaint();
                            a *= -1;
                            tremoloOperators[j]->toBehind(sampler1Operators[i]);
                            if (fGraph.isConnected(samp1Nodes[i]->nodeId,tremoloNodes[j]->nodeId))
                                prevMin = j;
                            if (min < 0) {
                                min = j;
                                minDistance = c;
                            } else if (c < minDistance) {
                                minDistance = c;
                                min = j;
                            }
                        }
                        else {
                            //TODO
                            if (fGraph.isConnected(samp1Nodes[i]->nodeId,tremoloNodes[j]->nodeId)) {
                                /* samp1 may already be connected to output node */
                                fGraph.addConnection(samp1Nodes[i]->nodeId, 0,
                                                     fOutputNode->nodeId, 0);
                                fGraph.addConnection(samp1Nodes[i]->nodeId, 1,
                                                     fOutputNode->nodeId, 1);
                                if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 0,
                                                            tremoloNodes[j]->nodeId, 0))
                                if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 1,
                                                            tremoloNodes[j]->nodeId, 1)) {
                                    componentMovedOrResized(*tremoloOperators[j], true, false);
                                    log->outputDebugString("disconnection successful");
                                    //sineOperators[i]->setTriggered(false);
                                }
                            }
                        }
                    }
                    if (min!=prevMin && prevMin >= 0)
                    if(fGraph.removeConnection(samp1Nodes[i]->nodeId,0,tremoloNodes[prevMin]->nodeId,0))
                    if(fGraph.removeConnection(samp1Nodes[i]->nodeId,1,tremoloNodes[prevMin]->nodeId,1)) {
                        log->outputDebugString("removed previous connection");
                        //sineOperators[i]->setTriggered(false);
                    }
                    if (min >= 0) {
                        if (!fGraph.isConnected(samp1Nodes[i]->nodeId, tremoloNodes[min]->nodeId))
                        if (fGraph.addConnection(samp1Nodes[i]->nodeId, 0, tremoloNodes[min]->nodeId, 0))
                        if (fGraph.addConnection(samp1Nodes[i]->nodeId, 1, tremoloNodes[min]->nodeId, 1))
                        if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 0, fOutputNode->nodeId, 0))
                        if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 1, fOutputNode->nodeId, 1))
                            log->outputDebugString("connection successful");
                        //sineOperators[i]->setTriggered(true);
                    }
                    minDistance = -1.0f;
                    min = -1;
                    prevMin=-1;
                    for (int j = 0; j < delayOperators.size(); ++j) {
                        a=sampler1Operators[i]->getX()+sampler1Operators[i]->getWidth()*0.5-(delayOperators[j]->getX()+delayOperators[j]->getWidth()*0.5);
                        b=sampler1Operators[i]->getY()+sampler1Operators[i]->getHeight()*0.5-(delayOperators[j]->getY()+delayOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        //TODO delayDistance
                        if (c < tremoloDistance) {
                            delayOperators[j]->repaint();
                            a *= -1;
                            delayOperators[j]->toBehind(sampler1Operators[i]);
                            if (fGraph.isConnected(samp1Nodes[i]->nodeId,delayNodes[j]->nodeId))
                                prevMin = j;
                            if (min < 0) {
                                min = j;
                                minDistance = c;
                            } else if (c < minDistance) {
                                minDistance = c;
                                min = j;
                            }
                        }
                        else {
                            //TODO
                            if (fGraph.isConnected(samp1Nodes[i]->nodeId,delayNodes[j]->nodeId)) {
                                /* samp1 may already be connected to output node */
                                fGraph.addConnection(samp1Nodes[i]->nodeId, 0,
                                                     fOutputNode->nodeId, 0);
                                fGraph.addConnection(samp1Nodes[i]->nodeId, 1,
                                                     fOutputNode->nodeId, 1);
                                if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 0,
                                                            delayNodes[j]->nodeId, 0))
                                if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 1,
                                                            delayNodes[j]->nodeId, 1)) {
                                    componentMovedOrResized(*delayOperators[j], true, false);
                                    log->outputDebugString("disconnection successful");
                                    //sineOperators[i]->setTriggered(false);
                                }
                            }
                        }
                    }
                    if (min!=prevMin && prevMin >= 0)
                    if(fGraph.removeConnection(samp1Nodes[i]->nodeId,0,delayNodes[prevMin]->nodeId,0))
                    if(fGraph.removeConnection(samp1Nodes[i]->nodeId,1,delayNodes[prevMin]->nodeId,1)) {
                        log->outputDebugString("removed previous connection");
                        //sineOperators[i]->setTriggered(false);
                    }
                    if (min >= 0) {
                        if (!fGraph.isConnected(samp1Nodes[i]->nodeId, delayNodes[min]->nodeId))
                        if (fGraph.addConnection(samp1Nodes[i]->nodeId, 0, delayNodes[min]->nodeId, 0))
                        if (fGraph.addConnection(samp1Nodes[i]->nodeId, 1, delayNodes[min]->nodeId, 1))
                        if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 0, fOutputNode->nodeId, 0))
                        if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 1, fOutputNode->nodeId, 1))
                            log->outputDebugString("connection successful");
                        //sineOperators[i]->setTriggered(true);
                    }
                    minDistance = -1.0f;
                    min = -1;
                    prevMin=-1;
                    for (int j = 0; j < echoOperators.size(); ++j) {
                        a=sampler1Operators[i]->getX()+sampler1Operators[i]->getWidth()*0.5-(echoOperators[j]->getX()+echoOperators[j]->getWidth()*0.5);
                        b=sampler1Operators[i]->getY()+sampler1Operators[i]->getHeight()*0.5-(echoOperators[j]->getY()+echoOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        //TODO echoDistance
                        if (c < tremoloDistance) {
                            echoOperators[j]->repaint();
                            a *= -1;
                            echoOperators[j]->toBehind(sampler1Operators[i]);
                            if (fGraph.isConnected(samp1Nodes[i]->nodeId,echoNodes[j]->nodeId))
                                prevMin = j;
                            if (min < 0) {
                                min = j;
                                minDistance = c;
                            } else if (c < minDistance) {
                                minDistance = c;
                                min = j;
                            }
                        }
                        else {
                            //TODO
                            if (fGraph.isConnected(samp1Nodes[i]->nodeId,echoNodes[j]->nodeId)) {
                                /* samp1 may already be connected to output node */
                                fGraph.addConnection(samp1Nodes[i]->nodeId, 0,
                                                     fOutputNode->nodeId, 0);
                                fGraph.addConnection(samp1Nodes[i]->nodeId, 1,
                                                     fOutputNode->nodeId, 1);
                                if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 0,
                                                            echoNodes[j]->nodeId, 0))
                                if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 1,
                                                            echoNodes[j]->nodeId, 1)) {
                                    componentMovedOrResized(*echoOperators[j], true, false);
                                    log->outputDebugString("disconnection successful");
                                    //sineOperators[i]->setTriggered(false);
                                }
                            }
                        }
                    }
                    if (min!=prevMin && prevMin >= 0)
                    if(fGraph.removeConnection(samp1Nodes[i]->nodeId,0,echoNodes[prevMin]->nodeId,0))
                    if(fGraph.removeConnection(samp1Nodes[i]->nodeId,1,echoNodes[prevMin]->nodeId,1)) {
                        log->outputDebugString("removed previous connection");
                        //sineOperators[i]->setTriggered(false);
                    }
                    if (min >= 0) {
                        if (!fGraph.isConnected(samp1Nodes[i]->nodeId, echoNodes[min]->nodeId))
                        if (fGraph.addConnection(samp1Nodes[i]->nodeId, 0, echoNodes[min]->nodeId, 0))
                        if (fGraph.addConnection(samp1Nodes[i]->nodeId, 1, echoNodes[min]->nodeId, 1))
                        if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 0, fOutputNode->nodeId, 0))
                        if (fGraph.removeConnection(samp1Nodes[i]->nodeId, 1, fOutputNode->nodeId, 1))
                            log->outputDebugString("connection successful");
                        //sineOperators[i]->setTriggered(true);
                    }
                    return;
                }
            }
            for (int i = 0; i < playOperators.size(); ++i){
                if (&component == playOperators[i]) {
                    playOperators[i]->toFront(true);
                    for (int j = 0; j < sampler1Operators.size(); ++j) {
                        a=playOperators[i]->getX()+playOperators[i]->getWidth()*0.5f-(sampler1Operators[j]->getX()+sampler1Operators[j]->getWidth()*0.5f);
                        b=playOperators[i]->getY()+playOperators[i]->getHeight()*0.5f-(sampler1Operators[j]->getY()+sampler1Operators[j]->getHeight()*0.5f);
                        c = std::sqrt(a*a+b*b);
                        //TODO replace tremoloDistance with something like playDistance, or distance
                        if (c < tremoloDistance) {
                            playOperators[i]->sampler1WithinTriggerDistance(j,true);
                            sampler1Operators[j]->setTriggered(true);
                            //componentMovedOrResized(*sineOperators[j], true, false);
                            sampler1Operators[j]->toBehind(playOperators[i]);
                            playOperators[i]->repaint();
                            sampler1Operators[j]->repaint();
                        }
                        else {
                            sampler1Operators[j]->setTriggered(false);
                            playOperators[i]->sampler1WithinTriggerDistance(j,false);
                            playOperators[i]->repaint();
                            sampler1Operators[j]->repaint();
                        }
                    }
                }
            }
            for (int i = 0; i < delayOperators.size(); ++i) {
                if (&component == delayOperators[i]) {
                    delayOperators[i]->toFront(true);
                    for (int j = 0; j < sampler1Operators.size(); ++j) {
                        a=delayOperators[i]->getX()+delayOperators[i]->getWidth()*0.5-(sampler1Operators[j]->getX()+sampler1Operators[j]->getWidth()*0.5);
                        b=delayOperators[i]->getY()+delayOperators[i]->getHeight()*0.5-(sampler1Operators[j]->getY()+sampler1Operators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        //TODO change tremoloDistance to something like delayDistance
                        if (c < tremoloDistance) {
                            componentMovedOrResized(*sampler1Operators[j], true, false);
                            sampler1Operators[j]->toBehind(delayOperators[i]);
                        }
                        else {
                            if (fGraph.isConnected(samp1Nodes[j]->nodeId,delayNodes[i]->nodeId)) {
                                fGraph.addConnection(samp1Nodes[j]->nodeId, 0,
                                                     fOutputNode->nodeId, 0);
                                fGraph.addConnection(samp1Nodes[j]->nodeId, 1,
                                                     fOutputNode->nodeId, 1);
                                if (fGraph.removeConnection(samp1Nodes[j]->nodeId, 0,
                                                                        delayNodes[i]->nodeId,
                                                                        0)) if (fGraph.removeConnection(
                                        samp1Nodes[j]->nodeId, 1, delayNodes[i]->nodeId, 1)) {
                                    //repaint();
                                    //sineOperators[j]->setTriggered(false);
                                    componentMovedOrResized(*sampler1Operators[j], true, false);
                                    log->outputDebugString("disconnection successful");
                                }
                            }
                        }
                    }
                    //TODO change to sineOperator
                    for (int j = 0; j < sineOperators.size(); ++j) {
                        a=delayOperators[i]->getX()+delayOperators[i]->getWidth()*0.5-(sineOperators[j]->getX()+sineOperators[j]->getWidth()*0.5);
                        b=delayOperators[i]->getY()+delayOperators[i]->getHeight()*0.5-(sineOperators[j]->getY()+sineOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        //TODO change tremoloDistance to something like delayDistance
                        if (c < tremoloDistance) {
                            componentMovedOrResized(*sineOperators[j], true, false);
                            sineOperators[j]->toBehind(delayOperators[i]);
                        }
                        else {
                            if (fGraph.isConnected(sineNodes[j]->nodeId,delayNodes[i]->nodeId)) {
                                fGraph.addConnection(sineNodes[j]->nodeId, 0,
                                                     fOutputNode->nodeId, 0);
                                fGraph.addConnection(sineNodes[j]->nodeId, 1,
                                                     fOutputNode->nodeId, 1);
                                if (fGraph.removeConnection(sineNodes[j]->nodeId, 0,
                                                            delayNodes[i]->nodeId,
                                                            0)) if (fGraph.removeConnection(
                                        sineNodes[j]->nodeId, 1, delayNodes[i]->nodeId, 1)) {
                                    //repaint();
                                    //sineOperators[j]->setTriggered(false);
                                    componentMovedOrResized(*sineOperators[j], true, false);
                                    log->outputDebugString("disconnection successful");
                                }
                            }
                        }
                    }
                    return;
                }
            }
            //TODO echo component was moved
            for (int i = 0; i < echoOperators.size(); ++i) {
                if (&component == echoOperators[i]) {
                    echoOperators[i]->toFront(true);
                    for (int j = 0; j < sampler1Operators.size(); ++j) {
                        a=echoOperators[i]->getX()+echoOperators[i]->getWidth()*0.5-(sampler1Operators[j]->getX()+sampler1Operators[j]->getWidth()*0.5);
                        b=echoOperators[i]->getY()+echoOperators[i]->getHeight()*0.5-(sampler1Operators[j]->getY()+sampler1Operators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        //TODO change tremoloDistance to something like echoDistance
                        if (c < tremoloDistance) {
                            componentMovedOrResized(*sampler1Operators[j], true, false);
                            sampler1Operators[j]->toBehind(echoOperators[i]);
                        }
                        else {
                            if (fGraph.isConnected(samp1Nodes[j]->nodeId,echoNodes[i]->nodeId)) {
                                fGraph.addConnection(samp1Nodes[j]->nodeId, 0,
                                                     fOutputNode->nodeId, 0);
                                fGraph.addConnection(samp1Nodes[j]->nodeId, 1,
                                                     fOutputNode->nodeId, 1);
                                if (fGraph.removeConnection(samp1Nodes[j]->nodeId, 0,
                                                            echoNodes[i]->nodeId,
                                                            0)) if (fGraph.removeConnection(
                                        samp1Nodes[j]->nodeId, 1, echoNodes[i]->nodeId, 1)) {
                                    //repaint();
                                    //sineOperators[j]->setTriggered(false);
                                    componentMovedOrResized(*sampler1Operators[j], true, false);
                                    log->outputDebugString("disconnection successful");
                                }
                            }
                        }
                    }
                    //TODO change to sineOperator
                    for (int j = 0; j < sineOperators.size(); ++j) {
                        a=echoOperators[i]->getX()+echoOperators[i]->getWidth()*0.5-(sineOperators[j]->getX()+sineOperators[j]->getWidth()*0.5);
                        b=echoOperators[i]->getY()+echoOperators[i]->getHeight()*0.5-(sineOperators[j]->getY()+sineOperators[j]->getHeight()*0.5);
                        c = std::sqrt(a*a+b*b);
                        //TODO change tremoloDistance to something like echoDistance
                        if (c < tremoloDistance) {
                            componentMovedOrResized(*sineOperators[j], true, false);
                            sineOperators[j]->toBehind(echoOperators[i]);
                        }
                        else {
                            if (fGraph.isConnected(sineNodes[j]->nodeId,echoNodes[i]->nodeId)) {
                                fGraph.addConnection(sineNodes[j]->nodeId, 0,
                                                     fOutputNode->nodeId, 0);
                                fGraph.addConnection(sineNodes[j]->nodeId, 1,
                                                     fOutputNode->nodeId, 1);
                                if (fGraph.removeConnection(sineNodes[j]->nodeId, 0,
                                                            echoNodes[i]->nodeId,
                                                            0)) if (fGraph.removeConnection(
                                        sineNodes[j]->nodeId, 1, echoNodes[i]->nodeId, 1)) {
                                    //repaint();
                                    //sineOperators[j]->setTriggered(false);
                                    componentMovedOrResized(*sineOperators[j], true, false);
                                    log->outputDebugString("disconnection successful");
                                }
                            }
                        }
                    }
                    return;
                }
            }
        }
    }

    void MainContentComponent::mouseDoubleClick(const MouseEvent &event) {
        Logger *log = Logger::getCurrentLogger();
        log->outputDebugString("something was clicked");
        SineOperatorContentComponent *componentSet = nullptr, *componentUnset = nullptr;
        Sampler1OperatorContentComponent *sampler1ComponentSet = nullptr, *sampler1ComponentUnset = nullptr;
        TremoloOperatorContentComponent *tremoloComponentSet = nullptr, *tremoloComponentUnset = nullptr;
        DelayOperatorContentComponent *delayComponentSet = nullptr, *delayComponentUnset = nullptr;
        EchoOperatorContentComponent *echoComponentSet = nullptr, *echoComponentUnset = nullptr;
        RadarTriggerComponent *radarComponentSet = nullptr, *radarComponentUnset = nullptr;
        for (int i = 0; i < sineOperators.size(); ++i) {
            sineVolSlider[i]->setVisible(false);
            sineFreqSlider[i]->setVisible(false);
            if (sineOperators[i]->isClicked()){
                if(sineOperators[i]->isMostRecentlyDoubleClicked()) {
                    log->outputDebugString(String (i) + " was most recently clicked");
                    componentUnset = sineOperators[i];
                }
                else {
                    log->outputDebugString(String (i) + " is most recently clicked");
                    componentSet = sineOperators[i];
                    sineVolSlider[i]->setVisible(true);
                    sineFreqSlider[i]->setVisible(true);
                }
            }
        }
        if (componentSet != nullptr) {
            log->outputDebugString("componentSet is not null");
            componentSet->setMostRecentlyDoubleClicked(true);
        }
        if (componentUnset != nullptr) {
            log->outputDebugString("componentUnset is not null");
            componentUnset->setMostRecentlyDoubleClicked(false);
            componentUnset->setClicked(false);
        }
        if (componentSet != nullptr || componentUnset != nullptr)
            return;
        for (int i = 0; i < tremoloOperators.size(); ++i) {
            tremoloIntensitySlider[i]->setVisible(false);
            tremoloFreqSlider[i]->setVisible(false);
            if (tremoloOperators[i]->isClicked()){
                if(tremoloOperators[i]->isMostRecentlyDoubleClicked()) {
                    log->outputDebugString("Tremolo component " + String (i) + " was most recently clicked");
                    tremoloComponentUnset = tremoloOperators[i];
                }
                else {
                    log->outputDebugString("Tremolo component " + String (i) + " is most recently clicked");
                    tremoloComponentSet = tremoloOperators[i];
                    tremoloIntensitySlider[i]->setVisible(true);
                    tremoloFreqSlider[i]->setVisible(true);
                }
            }
        }
        if (tremoloComponentSet != nullptr) {
            log->outputDebugString("tremoloComponentSet is not null");
            tremoloComponentSet->setMostRecentlyDoubleClicked(true);
        }
        if (tremoloComponentUnset != nullptr) {
            log->outputDebugString("tremoloComponentUnset is not null");
            tremoloComponentUnset->setMostRecentlyDoubleClicked(false);
            tremoloComponentUnset->setClicked(false);
        }
        if (tremoloComponentSet != nullptr || tremoloComponentUnset != nullptr)
            return;
        for (int i = 0; i < sampler1Operators.size(); ++i) {
            sampler1VolSlider[i]->setVisible(false);
            if (sampler1Operators[i]->isClicked()){
                if(sampler1Operators[i]->isMostRecentlyDoubleClicked()) {
                    log->outputDebugString("Tremolo component " + String (i) + " was most recently clicked");
                    sampler1ComponentUnset = sampler1Operators[i];
                }
                else {
                    log->outputDebugString("Tremolo component " + String (i) + " is most recently clicked");
                    sampler1ComponentSet = sampler1Operators[i];
                    sampler1VolSlider[i]->setVisible(true);
                }
            }
        }
        if (sampler1ComponentSet != nullptr) {
            log->outputDebugString("sampler1ComponentSet is not null");
            sampler1ComponentSet->setMostRecentlyDoubleClicked(true);
        }
        if (sampler1ComponentUnset != nullptr) {
            log->outputDebugString("sampler1ComponentUnset is not null");
            sampler1ComponentUnset->setMostRecentlyDoubleClicked(false);
            sampler1ComponentUnset->setClicked(false);
        }
        if (sampler1ComponentSet != nullptr || sampler1ComponentUnset != nullptr)
            return;
        for (int i = 0; i < delayOperators.size(); ++i) {
            delaySlider[i]->setVisible(false);
            if (delayOperators[i]->isClicked()){
                if(delayOperators[i]->isMostRecentlyDoubleClicked()) {
                    log->outputDebugString("Delay component " + String (i) + " was most recently clicked");
                    delayComponentUnset = delayOperators[i];
                }
                else {
                    log->outputDebugString("Delay component " + String (i) + " is most recently clicked");
                    delayComponentSet = delayOperators[i];
                    delaySlider[i]->setVisible(true);
                }
            }
        }
        if (delayComponentSet != nullptr) {
            log->outputDebugString("delayComponentSet is not null");
            delayComponentSet->setMostRecentlyDoubleClicked(true);
        }
        if (delayComponentUnset != nullptr) {
            log->outputDebugString("delayComponentUnset is not null");
            delayComponentUnset->setMostRecentlyDoubleClicked(false);
            delayComponentUnset->setClicked(false);
        }
        if (delayComponentSet != nullptr || delayComponentUnset != nullptr)
            return;
        for (int i = 0; i < echoOperators.size(); ++i) {
            echoIntensitySlider[i]->setVisible(false);
            echoDelaySlider[i]->setVisible(false);
            if (echoOperators[i]->isClicked()){
                if(echoOperators[i]->isMostRecentlyDoubleClicked()) {
                    log->outputDebugString("Echo component " + String (i) + " was most recently clicked");
                    echoComponentUnset = echoOperators[i];
                }
                else {
                    log->outputDebugString("Echo component " + String (i) + " is most recently clicked");
                    echoComponentSet = echoOperators[i];
                    echoIntensitySlider[i]->setVisible(true);
                    echoDelaySlider[i]->setVisible(true);
                }
            }
        }
        if (echoComponentSet != nullptr) {
            log->outputDebugString("echoComponentSet is not null");
            echoComponentSet->setMostRecentlyDoubleClicked(true);
        }
        if (echoComponentUnset != nullptr) {
            log->outputDebugString("echoComponentUnset is not null");
            echoComponentUnset->setMostRecentlyDoubleClicked(false);
            echoComponentUnset->setClicked(false);
        }
        if (echoComponentSet != nullptr || echoComponentUnset != nullptr)
            return;
        for (int i = 0; i < radarTriggers.size(); ++i) {
            radarFreqSlider[i]->setVisible(false);
            radarLengthSlider[i]->setVisible(false);
            if (radarTriggers[i]->isClicked()){
                if(radarTriggers[i]->isMostRecentlyDoubleClicked()) {
                    log->outputDebugString("Radar component " + String (i) + " was most recently clicked");
                    radarComponentUnset = radarTriggers[i];
                }
                else {
                    log->outputDebugString("Radar component " + String (i) + " is most recently clicked");
                    radarComponentSet = radarTriggers[i];
                    radarFreqSlider[i]->setVisible(true);
                    radarLengthSlider[i]->setVisible(true);
                }
            }
        }
        if (radarComponentSet != nullptr) {
            log->outputDebugString("radarComponentSet is not null");
            radarComponentSet->setMostRecentlyDoubleClicked(true);
        }
        if (radarComponentUnset != nullptr) {
            log->outputDebugString("radarComponentUnset is not null");
            radarComponentUnset->setMostRecentlyDoubleClicked(false);
            radarComponentUnset->setClicked(false);
        }
    }

    void MainContentComponent::hiResTimerCallback() {
        Logger *log = Logger::getCurrentLogger();
        double theta, cosTheta, sinTheta;
        int width, height, x, y;
        if (radarRefresh++ > 10) {
            radarRefresh = 0;
            for (int i = 0; i < radarTriggers.size(); ++i) {
                theta = radarTriggers[i]->getTheta();
                cosTheta = std::cos(theta);
                sinTheta = std::sin(theta);
                width = radarTriggers[i]->getWidth();
                height = radarTriggers[i]->getHeight();
                x = radarTriggers[i]->getX();
                y = radarTriggers[i]->getY();
                //repaint(radarTriggers[i]->getX()-150,radarTriggers[i]->getY()-150,radarTriggers[i]->getWidth()+300,radarTriggers[i]->getHeight()+300);
                if (theta < double_Pi/2)
                    repaint(x+int(width*0.5f), y+int(height*0.5f),radarTriggers[i]->getRadarDistance(),radarTriggers[i]->getRadarDistance());
                else if (theta < double_Pi)
                    repaint(x+int(width*0.5f)-radarTriggers[i]->getRadarDistance(),y+int(height*0.5f),radarTriggers[i]->getRadarDistance(),radarTriggers[i]->getRadarDistance());
                else if (theta < double_Pi*3/2)
                    repaint(x+int(width*0.5f)-radarTriggers[i]->getRadarDistance(),y+int(height*0.5f)-radarTriggers[i]->getRadarDistance(),radarTriggers[i]->getRadarDistance(),radarTriggers[i]->getRadarDistance());
                else
                    repaint(x+int(width*0.5f),y+int(height*0.5f)-radarTriggers[i]->getRadarDistance(),radarTriggers[i]->getRadarDistance(),radarTriggers[i]->getRadarDistance());
            }
        }
        for (int i = 0; i < radarTriggers.size(); ++i) {
            /*
            for (int j = 0; j < sineOperators.size(); ++j) {
                if ( std::abs(radarTriggers[i]->getAngleBetween(j)-radarTriggers[i]->getTheta()) < 0.1 && radarTriggers[i]->isWithinTriggerDistance(j)) {
                    sineOperators[j]->setTriggered(true);
                }
                else {
                    sineOperators[j]->setTriggered(false);
                }
            }
             */
            for (int j = 0; j < sineOperators.size(); ++j) {
                if ( std::abs(radarTriggers[i]->getAngleBetween(j)-radarTriggers[i]->getTheta()) < 0.1 && radarTriggers[i]->isWithinTriggerDistance(j)) {
                    sineOperators[j]->setTriggered(true);
                }
            }
        }
    }


// (This function is called by the app startup code to create our main component)



