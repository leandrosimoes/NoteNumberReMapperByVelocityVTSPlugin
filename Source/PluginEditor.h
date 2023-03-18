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

    GroupComponent groups[22];

    Slider sliders[22];

    ComboBox comboboxesIn[22];
    ComboBox comboboxesOut[22];

    std::unique_ptr<SliderAttachment> sliderAttatchments[22];
    std::unique_ptr<ComboBoxAttatchment> comboboxInAttatchments[22];
    std::unique_ptr<ComboBoxAttatchment> comboboxOutAttatchments[22];
    
    TextButton resetButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoteNumberRemaperByVelocityAudioProcessorEditor)
};
