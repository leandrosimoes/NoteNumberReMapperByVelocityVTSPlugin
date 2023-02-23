/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

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

    Label titleLabel;
    Label hihatLabel;
    Label crashLeftLabel;
    Label crashRightLabel;

    Slider hihatSlider;
    Slider crashLeftSlider;
    Slider crashRightSlider;

    std::unique_ptr<SliderAttachment> hihatSliderAttachment;
    std::unique_ptr<SliderAttachment> crashLeftSliderAttachment;
    std::unique_ptr<SliderAttachment> crashRightSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteNumberRemaperByVelocityAudioProcessorEditor)
};
