/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MidiProcessor.h"

//==============================================================================
/**
*/
class NoteNumberRemaperByVelocityAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    NoteNumberRemaperByVelocityAudioProcessor();
    ~NoteNumberRemaperByVelocityAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setHiHatVelocity(double value) {
        midiProcessor.hihatVelocity = hihatVelocity;
    }

    void setCrashLeftVelocity(double value) {
        midiProcessor.crashLeftVelocity = crashLeftVelocity;
    }

    void setCrashRightVelocity(double value) {
        midiProcessor.crashRightVelocity = crashRightVelocity;
    }

    AudioProcessorValueTreeState parameters;

    std::atomic<float>* hihatVelocity = nullptr;
    std::atomic<float>* crashLeftVelocity = nullptr;
    std::atomic<float>* crashRightVelocity = nullptr;

private:
    MidiProcessor midiProcessor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteNumberRemaperByVelocityAudioProcessor)
};
