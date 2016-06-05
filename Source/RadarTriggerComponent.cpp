/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include <src/main/jni/BinaryData.h>
#include <src/main/jni/AppConfig.h>
#include "RadarTriggerComponent.h"
#include "TremoloPluginEditor.h"


//==============================================================================
    RadarTriggerComponent::RadarTriggerComponent() {
    }

RadarTriggerComponent::RadarTriggerComponent(Image image, double freq)
    :   angleDelta(0.0),
        doubleClick(false),
        distance(0),
        level(1),
        theta(double_Pi),
        counter(0)
    {
        this->image = image;
        this->freq = freq;
    }

    RadarTriggerComponent::~RadarTriggerComponent() {
        for (int i = 0; i < angles.size(); ++i) {
            angles.remove(0);
        }
        for (int i = 0; i < isWithinDistance.size(); ++i) {
            isWithinDistance.remove(0);
        }
    }

    void RadarTriggerComponent::paint(Graphics &g) {
        g.drawImageWithin(image, 0, 0, getWidth(), getHeight(),
                          RectanglePlacement::onlyReduceInSize, false);
    }

    void RadarTriggerComponent::resized() {
        // This is called when the RadarTriggerComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

//=======================================================================
    void RadarTriggerComponent::updateAngleDelta()
    {
        //const double cyclesPerSample = freq / currentSampleRate;
        //angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

//=======================================================================

    void RadarTriggerComponent::mouseDown(const MouseEvent &e) {
        myDragger.startDraggingComponent(this, e);
    }

    void RadarTriggerComponent::mouseDrag(const MouseEvent &e) {
        myDragger.dragComponent(this, e, nullptr);
    }

    void RadarTriggerComponent::mouseDoubleClick(const MouseEvent &e) {
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

    void RadarTriggerComponent::sliderValueChanged(Slider *slider) {
    }

    bool RadarTriggerComponent::isClicked() {
        return doubleClick;
    }

    void RadarTriggerComponent::setClicked(bool doubleClick) {
        this->doubleClick = doubleClick;
    }

    bool RadarTriggerComponent::isMostRecentlyDoubleClicked() {
        return mostRecentlyDoubleClicked;
    }

    void RadarTriggerComponent::setMostRecentlyDoubleClicked(bool mostRecentlyDoubleClicked) {
        this->mostRecentlyDoubleClicked = mostRecentlyDoubleClicked;
    }

    float RadarTriggerComponent::getLevel() {
        return level;
    }

    void RadarTriggerComponent::sliderDragStarted(Slider *slider) {
    }

    void RadarTriggerComponent::sliderDragEnded(Slider *slider) {
    }

    void RadarTriggerComponent::hiResTimerCallback() {
        theta = theta + freq*2*double_Pi/1000;
        if (theta > 2*double_Pi) {
            theta = theta-2*double_Pi;
        }
        counter++;
    }

    double RadarTriggerComponent::getTheta() {
        return theta;
    }

    void RadarTriggerComponent::setTheta(double theta) {
        this->theta = theta;
    }

    double RadarTriggerComponent::getFreq() {
        return freq;
    }

    void RadarTriggerComponent::setFreq(double freq) {
        this->freq = freq;
    }

    void RadarTriggerComponent::setAngleBetween(int kOperatorIndex, double angle) {
        while (angles.size() < kOperatorIndex) {
            angles.add(0.0);
        }
        if (angles.size() == kOperatorIndex)
            angles.add(angle);
        else
            angles.set(kOperatorIndex, angle);
    }

    double RadarTriggerComponent::getAngleBetween(int kOperatorIndex) {
        return angles[kOperatorIndex];
    }

    void RadarTriggerComponent::withinTriggerDistance(int kOperatorIndex, bool isWithinDistance) {
        while(this->isWithinDistance.size() < kOperatorIndex) {
            this->isWithinDistance.add(false);
        }
        if (this->isWithinDistance.size() == kOperatorIndex)
            this->isWithinDistance.add(isWithinDistance);
        else
            this->isWithinDistance.set(kOperatorIndex, isWithinDistance);
    }

    bool RadarTriggerComponent::isWithinTriggerDistance(int kOperatorIndex) {
        return isWithinDistance[kOperatorIndex];
    }

    int RadarTriggerComponent::getRadarDistance() {
        return radarDistance;
    }

    void RadarTriggerComponent::setRadarDistance(int radarDistance) {
        this->radarDistance = radarDistance;
    }
