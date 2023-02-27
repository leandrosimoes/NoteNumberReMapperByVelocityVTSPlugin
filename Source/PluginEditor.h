/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttatchment;

//==============================================================================
/**
*/
class NoteNumberRemaperByVelocityAudioProcessorEditor  : public juce::AudioProcessorEditor, public Slider::Listener, public ComboBox::Listener
{
public:
    NoteNumberRemaperByVelocityAudioProcessorEditor (NoteNumberRemaperByVelocityAudioProcessor&);
    ~NoteNumberRemaperByVelocityAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;

    void comboBoxChanged(ComboBox* cb) override;

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

    ComboBox hihatNoteInCB;
    ComboBox hihatNoteOutCB;

    std::unique_ptr<SliderAttachment> hihatSliderAttachment;
    std::unique_ptr<SliderAttachment> crashLeftSliderAttachment;
    std::unique_ptr<SliderAttachment> crashRightSliderAttachment;

    std::unique_ptr<ComboBoxAttatchment> hihatNoteInCBAttachment;
    std::unique_ptr<ComboBoxAttatchment> hihatNoteOutCBAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteNumberRemaperByVelocityAudioProcessorEditor)
};
