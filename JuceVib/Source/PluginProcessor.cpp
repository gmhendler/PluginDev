/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JuceVibAudioProcessor::JuceVibAudioProcessor()
{
	Vib = 0;
	CMyProject::create(Vib);

}

JuceVibAudioProcessor::~JuceVibAudioProcessor()
{
	CMyProject::destroy(Vib);
}

bool JuceVibAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool JuceVibAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

double JuceVibAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

//==============================================================================
const String JuceVibAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int JuceVibAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceVibAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceVibAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceVibAudioProcessor::getProgramName (int index)
{
    return String();
}

void JuceVibAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceVibAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	Vib->init(2, sampleRate, (int)(sampleRate/2), 5, .5);
	maxFreq = 200;
}

void JuceVibAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JuceVibAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	if (bypassed) {
		processBlockBypassed(buffer, midiMessages);
	}
	else {

		const int totalNumInputChannels = getTotalNumInputChannels();
		const int totalNumOutputChannels = getTotalNumOutputChannels();

		//Set parameters
		lfoFreq = freqParam->get();
		lfoAmp = depthParam->get();

		Vib->setFreq(lfoFreq*maxFreq);
		Vib->setDepth(lfoAmp);

		// In case we have more outputs than inputs, this code clears any output
		// channels that didn't contain input data, (because these aren't
		// guaranteed to be empty - they may contain garbage).
		// This is here to avoid people getting screaming feedback
		// when they first compile a plugin, but obviously you don't need to keep
		// this code if your algorithm always overwrites all the output channels.
		for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
			buffer.clear(i, 0, buffer.getNumSamples());

		float** ppfWriteBuffer = buffer.getArrayOfWritePointers();
		Vib->process(ppfWriteBuffer, ppfWriteBuffer, buffer.getNumSamples());
	}
}

void JuceVibAudioProcessor::processBlockBypassed (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
}

//==============================================================================
bool JuceVibAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceVibAudioProcessor::createEditor()
{
    return new JuceVibAudioProcessorEditor (*this);
}

//==============================================================================
void JuceVibAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceVibAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceVibAudioProcessor();
}
