#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_dsp/juce_dsp.h>

class Oscillator
{
public:
    Oscillator();
    ~Oscillator();

    Oscillator(Oscillator&& other) noexcept;
    Oscillator& operator=(Oscillator&& other) noexcept;

    Oscillator(const Oscillator&) = delete;
    Oscillator& operator=(const Oscillator&) = delete;

    void prepare(const juce::dsp::ProcessSpec& spec); // Prepare the oscillator for processing
    void setFrequency(float frequency);              // Set the oscillator frequency
    void process(juce::dsp::AudioBlock<float>& audioBlock); // Process audio data

    void noteOn();
    void noteOff();
    void setADSRParameters(const juce::ADSR::Parameters& params);

private:
    juce::dsp::Oscillator<float> oscillator; // JUCE DSP oscillator
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
};

