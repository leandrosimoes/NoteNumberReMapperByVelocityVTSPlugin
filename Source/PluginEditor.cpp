/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoteNumberRemaperByVelocityAudioProcessorEditor::NoteNumberRemaperByVelocityAudioProcessorEditor (NoteNumberRemaperByVelocityAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 600);

    hihatSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    hihatSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    hihatSlider.setRange(0.0, 127.0, 1.0);
    hihatSlider.setValue(70.0);
    hihatSlider.addListener(this);

    crashLeftSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    crashLeftSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    crashLeftSlider.setRange(0.0, 127.0, 1.0);
    crashLeftSlider.setValue(70.0);
    crashLeftSlider.addListener(this);

    crashRightSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    crashRightSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    crashRightSlider.setRange(0.0, 127.0, 1.0);
    crashRightSlider.setValue(70.0);
    crashRightSlider.addListener(this);

    addAndMakeVisible(hihatSlider);
    addAndMakeVisible(crashLeftSlider);
    addAndMakeVisible(crashRightSlider);
}

NoteNumberRemaperByVelocityAudioProcessorEditor::~NoteNumberRemaperByVelocityAudioProcessorEditor()
{
}

//==============================================================================
void NoteNumberRemaperByVelocityAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    hihatSlider.setBounds(50, 50, 100, 400);
    crashLeftSlider.setBounds(200, 50, 100, 400);
    crashRightSlider.setBounds(350, 50, 100, 400);
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &hihatSlider)
        audioProcessor.setHiHatVelocity(slider->getValue());
    else if (slider == &crashLeftSlider)
        audioProcessor.setCrashLeftVelocity(slider->getValue());
    else if (slider == &crashRightSlider)
        audioProcessor.setCrashRightVelocity(slider->getValue());
}