#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class OscillatorViewComponent: public juce::Component
{
public:
    OscillatorViewComponent();
    ~OscillatorViewComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorViewComponent)

    juce::ComponentDragger dragger;
};
