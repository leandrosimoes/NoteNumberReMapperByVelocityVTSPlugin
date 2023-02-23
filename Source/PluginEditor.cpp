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
    setSize (500, 350);

    hihatSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    hihatSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    hihatSlider.setRange(0.0f, 127.0f, 1.0f);
    hihatSlider.setValue(70.0f);
    hihatSlider.addListener(this);

    crashLeftSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    crashLeftSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    crashLeftSlider.setRange(0.0f, 127.0f, 1.0f);
    crashLeftSlider.setValue(70.0f);
    crashLeftSlider.addListener(this);

    crashRightSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    crashRightSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    crashRightSlider.setRange(0.0f, 127.0f, 1.0f);
    crashRightSlider.setValue(70.0f);
    crashRightSlider.addListener(this);

    titleLabel.setText("Set the velocity break points", juce::dontSendNotification);
    titleLabel.setJustificationType(Justification::centred);

    hihatLabel.setText("HiHat", juce::dontSendNotification);
    hihatLabel.setJustificationType(Justification::centred);
    
    crashLeftLabel.setText("Crash L", juce::dontSendNotification);
    crashLeftLabel.setJustificationType(Justification::centred);
    
    crashRightLabel.setText("Crash R", juce::dontSendNotification);
    crashRightLabel.setJustificationType(Justification::centred);

    addAndMakeVisible(hihatSlider);
    addAndMakeVisible(crashLeftSlider);
    addAndMakeVisible(crashRightSlider);
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(hihatLabel);
    addAndMakeVisible(crashLeftLabel);
    addAndMakeVisible(crashRightLabel);

    hihatSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "hihatVelocity", hihatSlider));
    crashLeftSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "crashLeftVelocity", crashLeftSlider));
    crashRightSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "crashRightVelocity", crashRightSlider));
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

    hihatSlider.setBounds(50, 50, 100, 200);
    crashLeftSlider.setBounds(200, 50, 100, 200);
    crashRightSlider.setBounds(350, 50, 100, 200);

    titleLabel.setBounds(0, 10, getWidth(), 30);

    hihatLabel.setBounds(hihatSlider.getX(), hihatSlider.getHeight() + 50, hihatSlider.getWidth(), 30);
    crashLeftLabel.setBounds(crashLeftSlider.getX(), crashLeftSlider.getHeight() + 50, crashLeftSlider.getWidth(), 30);
    crashRightLabel.setBounds(crashRightSlider.getX(), crashRightSlider.getHeight() + 50, crashRightSlider.getWidth(), 30);
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &hihatSlider)
        audioProcessor.setHiHatVelocity(slider->getValue());
    else if (slider == &crashLeftSlider)
        audioProcessor.setCrashLeftVelocity(slider->getValue());
    else if (slider == &crashRightSlider)
        audioProcessor.setCrashRightVelocity(slider->getValue());
}