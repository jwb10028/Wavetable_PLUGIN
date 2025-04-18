#include "OscillatorViewComponent.h"

OscillatorViewComponent::OscillatorViewComponent()
{
    setInterceptsMouseClicks(true, true);
}

OscillatorViewComponent::~OscillatorViewComponent()
{
}

void OscillatorViewComponent::paint(juce::Graphics& g)
{
    // Fill the background with a color
    g.fillAll(juce::Colours::darkgrey);

    // Set the text color
    g.setColour(juce::Colours::white);

    // Set the font size
    g.setFont(20.0f);

    // Draw the message in the center of the component
    g.drawText("Hello from Oscillator Component", getLocalBounds(),
               juce::Justification::centred, true);
}

void OscillatorViewComponent::resized()
{
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

