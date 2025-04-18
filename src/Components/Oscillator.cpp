#include "Oscillator.h"

Oscillator::Oscillator()
{
    // Initialize the oscillator with a sine wave
    oscillator.initialise([](float x) { return std::sin(x); });
}

Oscillator::~Oscillator()
{
}

Oscillator::Oscillator(Oscillator&& other) noexcept
    : oscillator([](float x) { return std::sin(x); }) // RE-INITIALIZE
{
    oscillator = std::move(other.oscillator);
    adsr = std::move(other.adsr);
    adsrParams = other.adsrParams;
}

Oscillator& Oscillator::operator=(Oscillator&& other) noexcept
{
    if (this != &other)
    {
        oscillator = std::move(other.oscillator);
        adsr = std::move(other.adsr);
        adsrParams = other.adsrParams;
    }
    return *this;
}

void Oscillator::prepare(const juce::dsp::ProcessSpec& spec)
{
    oscillator.prepare(spec);
    oscillator.initialise([](float x) { return std::sin(x); }); // Ensure init
    adsr.setSampleRate(spec.sampleRate);
}

void Oscillator::setFrequency(float frequency)
{
    DBG("Set frequency: " << frequency);
    oscillator.setFrequency(frequency);
}

void Oscillator::setADSRParameters(const juce::ADSR::Parameters& params) {
    adsrParams = params;
    adsr.setParameters(adsrParams);
}

void Oscillator::noteOn() {
    DBG("Note ON");
    adsr.noteOn();
}

void Oscillator::noteOff() {
    adsr.noteOff();
}

void Oscillator::process(juce::dsp::AudioBlock<float>& audioBlock)
{
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    oscillator.process(context);

    juce::AudioBuffer<float> tempBuffer(
        static_cast<int>(audioBlock.getNumChannels()),
        static_cast<int>(audioBlock.getNumSamples())
    );

    for (size_t ch = 0; ch < audioBlock.getNumChannels(); ++ch)
        tempBuffer.copyFrom(static_cast<int>(ch), 0, audioBlock.getChannelPointer(ch), static_cast<int>(audioBlock.getNumSamples()));

    adsr.applyEnvelopeToBuffer(tempBuffer, 0, tempBuffer.getNumSamples());

    for (size_t ch = 0; ch < audioBlock.getNumChannels(); ++ch)
        std::memcpy(audioBlock.getChannelPointer(ch), tempBuffer.getReadPointer(static_cast<int>(ch)), sizeof(float) * tempBuffer.getNumSamples());
}

void Oscillator::setWaveformType(WaveformType type)
{
    switch (type)
    {
        case WaveformType::Sine:
            oscillator.initialise([](float x) { return std::sin(x); }, 128);
            break;
        case WaveformType::Saw:
            oscillator.initialise([](float x) { return x / juce::MathConstants<float>::pi; }, 128);
            break;
        case WaveformType::Triangle:
            oscillator.initialise([](float x) {
                return 2.0f * std::abs(2.0f * (x / juce::MathConstants<float>::twoPi - std::floor(x / juce::MathConstants<float>::twoPi + 0.5f))) - 1.0f;
            }, 128);
            break;
        case WaveformType::Square:
            oscillator.initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; }, 128);
            break;
    }
}

void Oscillator::setBaseFrequency(float baseFreq)
{
    currentBaseFreq = baseFreq;
    oscillator.setFrequency(currentBaseFreq * currentOffsetRatio);
}

void Oscillator::setPitchOffset(int octave, int semitones, float cents)
{
    float semitoneTotal = static_cast<float>(octave * 12 + semitones) + (cents / 100.0f);
    currentOffsetRatio = std::pow(2.0f, semitoneTotal / 12.0f);
    oscillator.setFrequency(currentBaseFreq * currentOffsetRatio);
}
