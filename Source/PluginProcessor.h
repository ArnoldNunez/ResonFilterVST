/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class ResonVstAudioProcessor  : public AudioProcessor,
	public AudioProcessorValueTreeState::Listener	///< For monitoring param changes
{
public:
    //==============================================================================
    ResonVstAudioProcessor();
    ~ResonVstAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResonVstAudioProcessor)

public:
	/// Name for the set of the reson filter parameters
	#define PARAM_RESON_SETNAME "ResonParamSet"
	#define PARAM_RESON_MASTERBYPASS "ResonBypass"
	#define PARAM_RESON_FREQ "ResonFreq"
	#define PARAM_RESON_BANDWIDTH "ResonBandwidth"

	AudioProcessorValueTreeState& getState() { return *mState; }
	void parameterChanged(const String& parameterID, float newValue) override { mMajorParamChange = true; }

private:
	/// True when there is a major param change
	bool mMajorParamChange;

	/// Reference to the value tree containing the state of the plugin
	ScopedPointer<AudioProcessorValueTreeState> mState;

	/// Reference to the undo manager
	ScopedPointer<UndoManager> mUndoManager;
};
