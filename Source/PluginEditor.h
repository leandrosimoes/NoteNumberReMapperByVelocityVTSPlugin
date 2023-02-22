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
class NoteNumberRemaperByVelocityAudioProcessorEditor  : public juce::AudioProcessorEditor, public Slider::Listener
{
public:
    NoteNumberRemaperByVelocityAudioProcessorEditor (NoteNumberRemaperByVelocityAudioProcessor&);
    ~NoteNumberRemaperByVelocityAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NoteNumberRemaperByVelocityAudioProcessor& audioProcessor;

    Slider hihatSlider;
    Slider crashLeftSlider;
    Slider crashRightSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteNumberRemaperByVelocityAudioProcessorEditor)
};
