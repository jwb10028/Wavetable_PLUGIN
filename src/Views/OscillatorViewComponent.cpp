#include "OscillatorViewComponent.h"

OscillatorViewComponent::OscillatorViewComponent()
{
    setInterceptsMouseClicks(true, true);

    // Waveform Selector
    waveformSelector.addItem("Sine", 1);
    waveformSelector.addItem("Saw", 2);
    waveformSelector.addItem("Triangle", 3);
    waveformSelector.addItem("Square", 4);
    waveformSelector.setSelectedId(1);
    addAndMakeVisible(waveformSelector);

    // Warp Mode Selector
    warpModeSelector.addItem("None", 1);
    warpModeSelector.addItem("FM", 2);
    warpModeSelector.addItem("AM", 3);
    warpModeSelector.setSelectedId(1);
    addAndMakeVisible(warpModeSelector);

    // Frequency Sliders
    octaveSlider.setRange(-4, 4, 1); // Octave range
    octaveSlider.setTextValueSuffix(" Oct");
    octaveSlider.setValue(0);
    addAndMakeVisible(octaveSlider);

    coarseSlider.setRange(-12, 12, 1); // Semitone range
    coarseSlider.setTextValueSuffix(" Semitones");
    coarseSlider.setValue(0);
    addAndMakeVisible(coarseSlider);

    fineSlider.setRange(-50, 50, 0.1); // Fine tuning in cents
    fineSlider.setTextValueSuffix(" Cents");
    fineSlider.setValue(0.0);
    addAndMakeVisible(fineSlider);

    // Level Slider
    levelSlider.setRange(0.0, 1.0, 0.01);
    levelSlider.setTextValueSuffix(" Level");
    levelSlider.setValue(1.0);
    addAndMakeVisible(levelSlider);

    // Warp Slider
    warpSlider.setRange(0.0, 1.0, 0.01);
    warpSlider.setTextValueSuffix(" Warp");
    warpSlider.setValue(0.0);
    addAndMakeVisible(warpSlider);

    // Unison Controls
    unisonVoicesSlider.setRange(1, 8, 1);
    unisonVoicesSlider.setTextValueSuffix(" Voices");
    unisonVoicesSlider.setValue(1);
    addAndMakeVisible(unisonVoicesSlider);

    detuneSlider.setRange(0.0, 100.0, 0.1);
    detuneSlider.setTextValueSuffix(" % Detune");
    detuneSlider.setValue(0.0);
    addAndMakeVisible(detuneSlider);

    blendSlider.setRange(0.0, 1.0, 0.01);
    blendSlider.setTextValueSuffix(" Blend");
    blendSlider.setValue(0.0);
    addAndMakeVisible(blendSlider);

    randomizePhaseButton.setButtonText("Randomize Phase");
    randomizePhaseButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(randomizePhaseButton);
}

OscillatorViewComponent::~OscillatorViewComponent()
{
}

void OscillatorViewComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
}

void OscillatorViewComponent::resized()
{
    auto area = getLocalBounds().reduced(10);

    // Layout controls
    waveformSelector.setBounds(area.removeFromTop(30));
    warpModeSelector.setBounds(area.removeFromTop(30));

    auto freqArea = area.removeFromTop(60);
    octaveSlider.setBounds(freqArea.removeFromLeft(freqArea.getWidth() / 3));
    coarseSlider.setBounds(freqArea.removeFromLeft(freqArea.getWidth() / 2));
    fineSlider.setBounds(freqArea);

    warpSlider.setBounds(area.removeFromTop(40));
    levelSlider.setBounds(area.removeFromTop(50));

    auto unisonArea = area.removeFromTop(60);
    unisonVoicesSlider.setBounds(unisonArea.removeFromLeft(unisonArea.getWidth() / 4));
    detuneSlider.setBounds(unisonArea.removeFromLeft(unisonArea.getWidth() / 3));
    blendSlider.setBounds(unisonArea.removeFromLeft(unisonArea.getWidth() / 2));
    randomizePhaseButton.setBounds(unisonArea);
}

void OscillatorViewComponent::mouseDown(const juce::MouseEvent& event)
{
    // Start dragging
    dragger.startDraggingComponent(this, event);
}

void OscillatorViewComponent::mouseDrag(const juce::MouseEvent& event)
{
    // Continue dragging
    dragger.dragComponent(this, event, nullptr);
}

