#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_dsp/juce_dsp.h>

class Oscillator
{
public:
    Oscillator();
    ~Oscillator();

    void prepare(const juce::dsp::ProcessSpec& spec); // Prepare the oscillator for processing
    void setFrequency(float frequency);              // Set the oscillator frequency
    void process(juce::dsp::AudioBlock<float>& audioBlock); // Process audio data

private:
    juce::dsp::Oscillator<float> oscillator; // JUCE DSP oscillator
};

