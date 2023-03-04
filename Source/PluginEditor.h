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

    void setupGroups();
    void setupNoteInCBs();
    void setupSliders();
    void setupNoteOutCBs();
    void setupResetButton();

    void comboBoxChanged(ComboBox* cb) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NoteNumberRemaperByVelocityAudioProcessor& audioProcessor;

    Label titleLabel;

    GroupComponent hihatGroup;
    GroupComponent crashLeftGroup;
    GroupComponent crashRightGroup;

    Slider hihatSlider;
    Slider crashLeftSlider;
    Slider crashRightSlider;

    ComboBox hihatNoteInCB;
    ComboBox hihatNoteOutCB;

    ComboBox crashLeftNoteInCB;
    ComboBox crashLeftNoteOutCB;

    ComboBox crashRightNoteInCB;
    ComboBox crashRightNoteOutCB;

    TextButton resetButton;

    std::unique_ptr<SliderAttachment> hihatSliderAttachment;
    std::unique_ptr<SliderAttachment> crashLeftSliderAttachment;
    std::unique_ptr<SliderAttachment> crashRightSliderAttachment;

    std::unique_ptr<ComboBoxAttatchment> hihatNoteInCBAttachment;
    std::unique_ptr<ComboBoxAttatchment> hihatNoteOutCBAttachment;

    std::unique_ptr<ComboBoxAttatchment> crashLeftNoteInCBAttachment;
    std::unique_ptr<ComboBoxAttatchment> crashLeftNoteOutCBAttachment;

    std::unique_ptr<ComboBoxAttatchment> crashRightNoteInCBAttachment;
    std::unique_ptr<ComboBoxAttatchment> crashRightNoteOutCBAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteNumberRemaperByVelocityAudioProcessorEditor)
};
