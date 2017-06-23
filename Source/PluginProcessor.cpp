/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static String GetStrValue(float v) { return String(v); }
static String GetBypassStr(float v) { return (v != 0.0f) ? "Bypassed" : "Enabled"; }


//==============================================================================
ResonVstAudioProcessor::ResonVstAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	mUndoManager = new UndoManager();
	mState = new AudioProcessorValueTreeState(*this, mUndoManager);

	// Add each of our parameters
	mState->createAndAddParameter(PARAM_RESON_MASTERBYPASS, "Bypass", "", NormalisableRange<float>(0, 1, 1),
		0, GetBypassStr, nullptr);
	mState->createAndAddParameter(PARAM_RESON_BANDWIDTH, "Bandwidth", "", NormalisableRange<float>(0.01, 1),
		0.01, nullptr, nullptr);
	mState->createAndAddParameter(PARAM_RESON_FREQ, "Frequency", "", NormalisableRange<float>(0, 0.5),
		0.045351f, nullptr, nullptr);

	// Create value tree state with Reson parameters
	mState->state = ValueTree(PARAM_RESON_SETNAME);

	// Add controls to trigger deeper update timed with the call to process
	// Such as: mState->addParameterListener(paramid, this);

	// Start with deep updates regardless
	mMajorParamChange = true;
}

ResonVstAudioProcessor::~ResonVstAudioProcessor()
{
	mState = nullptr;
	mUndoManager = nullptr;
}

//==============================================================================
const String ResonVstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ResonVstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ResonVstAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double ResonVstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ResonVstAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ResonVstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ResonVstAudioProcessor::setCurrentProgram (int index)
{
}

const String ResonVstAudioProcessor::getProgramName (int index)
{
    return {};
}

void ResonVstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ResonVstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ResonVstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ResonVstAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void ResonVstAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	if (mMajorParamChange)
	{
		// This is where to put code to reconfigure buffers or other
		// major changes that can occur

		mMajorParamChange = false;
	}

    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

	if (totalNumInputChannels != 2 || totalNumOutputChannels != 2
		|| (*mState->getRawParameterValue(PARAM_RESON_MASTERBYPASS)) != 0.0f)
	{
		// Do nothing- Only want to process audio when input channels match output channels
		// and our filter is not bypassed.
	}
	else
	{
		// Get array of pointers to channel data
		float** pChannelData = buffer.getArrayOfWritePointers();

		// Pass it on to the reson filter
		// mResonFilter.Process(pChannelData[0], pChannelData[1], buffer.getNumSamples());
	}
}

//==============================================================================
bool ResonVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ResonVstAudioProcessor::createEditor()
{
    return new ResonVstAudioProcessorEditor (*this);
}

//==============================================================================
void ResonVstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	MemoryOutputStream stream(destData, false);
	mState->state.writeToStream(stream);
}

void ResonVstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
	if (tree.isValid())
	{
		if (tree.hasType(PARAM_RESON_SETNAME))
		{
			mState->state = tree;
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ResonVstAudioProcessor();
}
