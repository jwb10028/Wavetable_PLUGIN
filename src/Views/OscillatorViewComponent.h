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

    std::function<void(int)> onWaveformChanged;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorViewComponent)

    juce::ComponentDragger dragger;

    // Waveform and Warp Mode Selectors
    juce::ComboBox waveformSelector;
    juce::ComboBox warpModeSelector;

    // Frequency Controls
    juce::Slider octaveSlider;
    juce::Slider coarseSlider;
    juce::Slider fineSlider;

    // Level Control
    juce::Slider levelSlider;

    // Warp Control
    juce::Slider warpSlider;

    // Unison Controls
    juce::Slider unisonVoicesSlider;
    juce::Slider detuneSlider;
    juce::Slider blendSlider;
    juce::ToggleButton randomizePhaseButton;
};
