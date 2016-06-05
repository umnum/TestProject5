/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include <src/main/jni/BinaryData.h>
#include <src/main/jni/AppConfig.h>
#include "PlayComponent.h"


//==============================================================================
    PlayComponent::PlayComponent() {
    }

PlayComponent::PlayComponent(Image image)
    :   doubleClick(false),
        distance(0),
        level(1)
    {
        this->image = image;
    }

    PlayComponent::~PlayComponent() {
    }

    void PlayComponent::paint(Graphics &g) {
        g.drawImageWithin(image, 0, 0, getWidth(), getHeight(),
                          RectanglePlacement::onlyReduceInSize, false);
    }

    void PlayComponent::resized() {
        // This is called when the PlayComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

//=======================================================================
    void PlayComponent::updateAngleDelta()
    {
        //const double cyclesPerSample = freq / currentSampleRate;
        //angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

//=======================================================================

    void PlayComponent::mouseDown(const MouseEvent &e) {
        myDragger.startDraggingComponent(this, e);
    }

    void PlayComponent::mouseDrag(const MouseEvent &e) {
        myDragger.dragComponent(this, e, nullptr);
    }

    void PlayComponent::mouseDoubleClick(const MouseEvent &e) {
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

    void PlayComponent::sliderValueChanged(Slider *slider) {
    }

    bool PlayComponent::isClicked() {
        return doubleClick;
    }

    void PlayComponent::setClicked(bool doubleClick) {
        this->doubleClick = doubleClick;
    }

    bool PlayComponent::isMostRecentlyDoubleClicked() {
        return mostRecentlyDoubleClicked;
    }

    void PlayComponent::setMostRecentlyDoubleClicked(bool mostRecentlyDoubleClicked) {
        this->mostRecentlyDoubleClicked = mostRecentlyDoubleClicked;
    }

    float PlayComponent::getLevel() {
        return level;
    }

    void PlayComponent::sliderDragStarted(Slider *slider) {
    }

    void PlayComponent::sliderDragEnded(Slider *slider) {
    }

    void PlayComponent::withinTriggerDistance(int kOperatorIndex, bool isWithinDistance) {
        while(this->isWithinDistance.size() < kOperatorIndex) {
            this->isWithinDistance.add(false);
        }
        if (this->isWithinDistance.size() == kOperatorIndex)
            this->isWithinDistance.add(isWithinDistance);
        else
            this->isWithinDistance.set(kOperatorIndex, isWithinDistance);
    }

    bool PlayComponent::isWithinTriggerDistance(int kOperatorIndex) {
        return isWithinDistance[kOperatorIndex];
    }

    void PlayComponent::sampler1WithinTriggerDistance(int sampler1Index, bool isWithinDistance) {
        while(this->sampler1IsWithinDistance.size() < sampler1Index) {
            this->sampler1IsWithinDistance.add(false);
        }
        if (this->sampler1IsWithinDistance.size() == sampler1Index)
            this->sampler1IsWithinDistance.add(isWithinDistance);
        else
            this->sampler1IsWithinDistance.set(sampler1Index, isWithinDistance);
    }

    bool PlayComponent::sampler1IsWithinTriggerDistance(int sampler1Index) {
        return sampler1IsWithinDistance[sampler1Index];
    }
