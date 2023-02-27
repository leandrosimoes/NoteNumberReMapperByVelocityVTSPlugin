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

    hihatNoteInCB.addSectionHeading("Note IN");
    hihatNoteInCB.addSeparator();
    hihatNoteOutCB.addSectionHeading("Note OUT");
    hihatNoteOutCB.addSeparator();

    for (int i = 127; i >= 0; i--) {
        hihatNoteInCB.addItem(std::to_string(i), i + 1);
        hihatNoteOutCB.addItem(std::to_string(i), i + 1);
    }
    hihatNoteInCB.setSelectedId(8);
    hihatNoteOutCB.setSelectedId(7);

    addAndMakeVisible(hihatSlider);
    addAndMakeVisible(crashLeftSlider);
    addAndMakeVisible(crashRightSlider);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(hihatLabel);
    addAndMakeVisible(crashLeftLabel);
    addAndMakeVisible(crashRightLabel);

    addAndMakeVisible(hihatNoteInCB);
    addAndMakeVisible(hihatNoteOutCB);

    hihatSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "hihatVelocity", hihatSlider));
    crashLeftSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "crashLeftVelocity", crashLeftSlider));
    crashRightSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "crashRightVelocity", crashRightSlider));

    hihatNoteInCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "hihatNoteIn", hihatNoteInCB));
    hihatNoteOutCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "hihatNoteOut", hihatNoteOutCB));
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

    hihatNoteOutCB.setBounds(50, 50, 100, 30);

    hihatSlider.setBounds(hihatNoteOutCB.getX(), hihatNoteOutCB.getY() + hihatNoteOutCB.getHeight() + 5, hihatNoteOutCB.getWidth(), 200);
    crashLeftSlider.setBounds(200, 100, 100, 200);
    crashRightSlider.setBounds(350, 100, 100, 200);

    hihatNoteInCB.setBounds(hihatSlider.getX(), hihatSlider.getY() + hihatSlider.getHeight() + 5, hihatSlider.getWidth(), 30);

    titleLabel.setBounds(0, 10, getWidth(), 30);

    hihatLabel.setBounds(hihatNoteInCB.getX(), hihatNoteInCB.getY() + 5, hihatNoteInCB.getWidth(), 30);
    crashLeftLabel.setBounds(crashLeftSlider.getX(), crashLeftSlider.getHeight() + 100, crashLeftSlider.getWidth(), 30);
    crashRightLabel.setBounds(crashRightSlider.getX(), crashRightSlider.getHeight() + 100, crashRightSlider.getWidth(), 30);

}

void NoteNumberRemaperByVelocityAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &hihatSlider)
        audioProcessor.hihatVelocity->store(slider->getValue());
    else if (slider == &crashLeftSlider)
        audioProcessor.crashLeftVelocity->store(slider->getValue());
    else if (slider == &crashRightSlider)
        audioProcessor.crashRightVelocity->store(slider->getValue());
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::comboBoxChanged(ComboBox* cb) {
    if (cb == &hihatNoteInCB)
        audioProcessor.hihatNoteIn->store(cb->getSelectedIdAsValue().getValue());
    if (cb == &hihatNoteOutCB)
        audioProcessor.hihatNoteOut->store(cb->getSelectedIdAsValue().getValue());
}