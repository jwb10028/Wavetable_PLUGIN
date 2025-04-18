#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 450);

    constrainer.setFixedAspectRatio(16.0 / 9.0);
    constrainer.setSizeLimits(400, 225, 1920, 1080);
    
    addAndMakeVisible(resizer);
    addAndMakeVisible(OscillatorViewA);
    addAndMakeVisible(keyboardComponent);

    OscillatorViewA.setBounds(0, 0, getWidth() / 2, getHeight() / 2);

    setResizable(true, true);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();
    auto oscillatorBounds = OscillatorViewA.getBounds();

    auto keyboardHeight = 100;
    keyboardComponent.setBounds(bounds.removeFromBottom(keyboardHeight));

    oscillatorBounds.setPosition(
        juce::jlimit(0, bounds.getWidth() - oscillatorBounds.getWidth(), oscillatorBounds.getX()),
        juce::jlimit(0, bounds.getHeight() - oscillatorBounds.getHeight(), oscillatorBounds.getY()));

    OscillatorViewA.setBounds(oscillatorBounds);
}
