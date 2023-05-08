#include "PluginProcessor.h"
#include "PluginEditor.h"

// Add this constant at the top of the file
const int numChannels = 8;

//==============================================================================
ES5ControllerAudioProcessorEditor::ES5ControllerAudioProcessorEditor (ES5ControllerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(120, 600);
}

ES5ControllerAudioProcessorEditor::~ES5ControllerAudioProcessorEditor()
{
}

//==============================================================================
void ES5ControllerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    for (int i = 0; i < numChannels; ++i)
    {
        int circleX = getWidth() / 2 - 30;
        int circleY = 15 + i * (60 + 15);

        float voltage = audioProcessor.getChannelVoltage(i);

        if (voltage > 0.0f)
            g.setColour(juce::Colours::red);
        else if (voltage < 0.0f)
            g.setColour(juce::Colours::blue);
        else
            g.setColour(juce::Colours::grey);

        g.fillEllipse(circleX, circleY, 60, 60);
    }
}

void ES5ControllerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
