#pragma once

#include "PluginProcessor.h"
#include "Views/OscillatorViewComponent.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)

    juce::ComponentBoundsConstrainer constrainer;
    juce::ResizableCornerComponent resizer { this, &constrainer };

    // Oscillator Windows
    OscillatorViewComponent OscillatorViewA;
    OscillatorViewComponent OscillatorViewB;
    OscillatorViewComponent OscillatorViewC;
};
