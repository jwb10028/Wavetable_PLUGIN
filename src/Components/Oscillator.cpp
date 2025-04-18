#include "Oscillator.h"

Oscillator::Oscillator()
{
    // Initialize the oscillator with a sine wave
    oscillator.initialise([](float x) { return std::sin(x); });
}

Oscillator::~Oscillator()
{
}

void Oscillator::prepare(const juce::dsp::ProcessSpec& spec)
{
    oscillator.prepare(spec);
}

void Oscillator::setFrequency(float frequency)
{
    oscillator.setFrequency(frequency);
}

void Oscillator::process(juce::dsp::AudioBlock<float>& audioBlock)
{
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    oscillator.process(context);
}
