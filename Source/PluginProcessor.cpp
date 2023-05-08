/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const int numChannels = 8;

//==============================================================================

ES5ControllerAudioProcessor::ES5ControllerAudioProcessor()
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         ),
      channelVoltages(numChannels, 0.0f) // Initialize channel voltages vector
{
}

float ES5ControllerAudioProcessor::getChannelVoltage(int channelIndex) const
{
    if (channelIndex >= 0 && channelIndex < channelVoltages.size())
    {
        return channelVoltages[channelIndex];
    }
    return 0.0f;
}

//==============================================================================
const juce::String ES5ControllerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ES5ControllerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ES5ControllerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ES5ControllerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ES5ControllerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ES5ControllerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ES5ControllerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ES5ControllerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ES5ControllerAudioProcessor::getProgramName (int index)
{
    return {};
}

void ES5ControllerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ES5ControllerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ES5ControllerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ES5ControllerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ES5ControllerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Peak detection code starts here
    float peak = 0.0f;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float currentSample = std::abs(channelData[sample]);
            if (currentSample > peak)
            {
                peak = currentSample;
            }
        }
    }

    float cvSignal = peak * 10.0f;
    // Peak detection code ends here
    
// Assuming that the output channels connected to the ES-5 module are
// immediately after the input channels in your audio interface
int firstEs5OutputChannel = totalNumInputChannels;
int numEs5OutputChannels = 8; // The number of output channels on the ES-5 module

// Iterate through the output channels connected to the ES-5 module
for (int channel = firstEs5OutputChannel; channel < firstEs5OutputChannel + numEs5OutputChannels; ++channel)
{
    auto* channelData = buffer.getWritePointer(channel);

    // Write the CV output signal to the corresponding samples in the output channel
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        channelData[sample] = cvSignal;
    }
}
        
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    /* Removed unused loop
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    */
}

//==============================================================================
bool ES5ControllerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ES5ControllerAudioProcessor::createEditor()
{
    return new ES5ControllerAudioProcessorEditor (*this);
}

//==============================================================================
void ES5ControllerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ES5ControllerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ES5ControllerAudioProcessor();
}
