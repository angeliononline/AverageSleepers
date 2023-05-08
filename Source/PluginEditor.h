/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ES5ControllerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ES5ControllerAudioProcessorEditor (ES5ControllerAudioProcessor&);
    ~ES5ControllerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ES5ControllerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ES5ControllerAudioProcessorEditor)
};
