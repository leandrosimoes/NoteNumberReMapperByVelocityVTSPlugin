/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 400;

//==============================================================================
NoteNumberRemaperByVelocityAudioProcessorEditor::NoteNumberRemaperByVelocityAudioProcessorEditor (NoteNumberRemaperByVelocityAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WINDOW_WIDTH, WINDOW_HEIGHT);

    titleLabel.setText("Set the velocity break points", juce::dontSendNotification);
    titleLabel.setJustificationType(Justification::centred);

    addAndMakeVisible(titleLabel);

    hihatSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    hihatSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    hihatSlider.setRange(0.0f, 127.0f, 1.0f);
    hihatSlider.setValue(70.0f);
    hihatSlider.addListener(this);

    hihatGroup.setText("HiHat");
    hihatGroup.setTextLabelPosition(Justification::centredTop);

    hihatNoteInCB.addSectionHeading("Note IN");
    hihatNoteInCB.addSeparator();
    hihatNoteInCB.addListener(this);

    hihatNoteOutCB.addSectionHeading("Note OUT");
    hihatNoteOutCB.addSeparator();
    hihatNoteOutCB.addListener(this);

    for (int i = 0; i <= 127; i++) {
        hihatNoteInCB.addItem(std::to_string(i), i + 1);
        hihatNoteOutCB.addItem(std::to_string(i), i + 1);
    }

    addAndMakeVisible(hihatGroup);
    addAndMakeVisible(hihatSlider);
    addAndMakeVisible(hihatNoteInCB);
    addAndMakeVisible(hihatNoteOutCB);

    hihatSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "hihatVelocity", hihatSlider));
    hihatNoteInCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "hihatNoteIn", hihatNoteInCB));
    hihatNoteOutCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "hihatNoteOut", hihatNoteOutCB));

    crashLeftSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    crashLeftSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    crashLeftSlider.setRange(0.0f, 127.0f, 1.0f);
    crashLeftSlider.setValue(70.0f);
    crashLeftSlider.addListener(this);

    crashLeftGroup.setText("Crash Left");
    crashLeftGroup.setTextLabelPosition(Justification::centredTop);

    crashLeftNoteInCB.addSectionHeading("Note IN");
    crashLeftNoteInCB.addSeparator();
    crashLeftNoteInCB.addListener(this);

    crashLeftNoteOutCB.addSectionHeading("Note OUT");
    crashLeftNoteOutCB.addSeparator();
    crashLeftNoteOutCB.addListener(this);

    for (int i = 0; i <= 127; i++) {
        crashLeftNoteInCB.addItem(std::to_string(i), i + 1);
        crashLeftNoteOutCB.addItem(std::to_string(i), i + 1);
    }

    addAndMakeVisible(crashLeftGroup);
    addAndMakeVisible(crashLeftSlider);
    addAndMakeVisible(crashLeftNoteInCB);
    addAndMakeVisible(crashLeftNoteOutCB);

    crashLeftSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "crashLeftVelocity", crashLeftSlider));
    crashLeftNoteInCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "crashLeftNoteIn", crashLeftNoteInCB));
    crashLeftNoteOutCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "crashLeftNoteOut", crashLeftNoteOutCB));

    crashRightSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    crashRightSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    crashRightSlider.setRange(0.0f, 127.0f, 1.0f);
    crashRightSlider.setValue(70.0f);
    crashRightSlider.addListener(this);

    crashRightGroup.setText("Crash Right");
    crashRightGroup.setTextLabelPosition(Justification::centredTop);

    crashRightNoteInCB.addSectionHeading("Note IN");
    crashRightNoteInCB.addSeparator();
    crashRightNoteInCB.addListener(this);

    crashRightNoteOutCB.addSectionHeading("Note OUT");
    crashRightNoteOutCB.addSeparator();
    crashRightNoteOutCB.addListener(this);

    for (int i = 0; i <= 127; i++) {
        crashRightNoteInCB.addItem(std::to_string(i), i + 1);
        crashRightNoteOutCB.addItem(std::to_string(i), i + 1);
    }

    addAndMakeVisible(crashRightGroup);
    addAndMakeVisible(crashRightSlider);
    addAndMakeVisible(crashRightNoteInCB);
    addAndMakeVisible(crashRightNoteOutCB);

    crashRightSliderAttachment.reset(new SliderAttachment(audioProcessor.parameters, "crashRightVelocity", crashRightSlider));
    crashRightNoteInCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "crashRightNoteIn", crashRightNoteInCB));
    crashRightNoteOutCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "crashRightNoteOut", crashRightNoteOutCB));

    resetButton.setButtonText("Reset");
    resetButton.onClick = [this]() {
        hihatNoteInCB.setSelectedId(9);
        hihatNoteOutCB.setSelectedId(8);
        crashLeftNoteInCB.setSelectedId(50);
        crashLeftNoteOutCB.setSelectedId(49);
        crashLeftNoteInCB.setSelectedId(58);
        crashLeftNoteOutCB.setSelectedId(57);

        hihatSlider.setValue(75.0f);
        crashLeftSlider.setValue(85.0f);
        crashRightSlider.setValue(85.0f);
    };

    addAndMakeVisible(resetButton);
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

    titleLabel.setBounds(0, 10, WINDOW_WIDTH, 30);

    hihatGroup.setBounds(50, titleLabel.getY() + titleLabel.getHeight() + 5, (WINDOW_WIDTH - 100) / 3, WINDOW_HEIGHT - 100);
    hihatNoteOutCB.setBounds(hihatGroup.getX() + 10, hihatGroup.getY() + 20, hihatGroup.getWidth() - 20, 30);
    hihatNoteInCB.setBounds(hihatGroup.getX() + 10, hihatGroup.getY() + hihatGroup.getHeight() - 40, hihatNoteOutCB.getWidth(), hihatNoteOutCB.getHeight());

    hihatSlider.setBounds(
        hihatNoteOutCB.getX(), 
        hihatNoteOutCB.getY() + hihatNoteOutCB.getHeight() + 5, 
        hihatNoteInCB.getWidth(),
        hihatGroup.getHeight() - hihatNoteInCB.getHeight() - hihatNoteOutCB.getHeight() - 40
    );

    crashLeftGroup.setBounds(hihatGroup.getX() + hihatGroup.getWidth() + 5, titleLabel.getY() + titleLabel.getHeight() + 5, hihatGroup.getWidth(), hihatGroup.getHeight());
    crashLeftNoteOutCB.setBounds(crashLeftGroup.getX() + 10, crashLeftGroup.getY() + 20, crashLeftGroup.getWidth() - 20, 30);
    crashLeftNoteInCB.setBounds(crashLeftGroup.getX() + 10, crashLeftGroup.getY() + crashLeftGroup.getHeight() - 40, crashLeftNoteOutCB.getWidth(), crashLeftNoteOutCB.getHeight());

    crashLeftSlider.setBounds(
        crashLeftNoteOutCB.getX(),
        crashLeftNoteOutCB.getY() + crashLeftNoteOutCB.getHeight() + 5,
        crashLeftNoteInCB.getWidth(),
        crashLeftGroup.getHeight() - crashLeftNoteInCB.getHeight() - crashLeftNoteOutCB.getHeight() - 40
    );

    crashRightGroup.setBounds(crashLeftGroup.getX() + crashLeftGroup.getWidth() + 5, titleLabel.getY() + titleLabel.getHeight() + 5, crashLeftGroup.getWidth(), crashLeftGroup.getHeight());
    crashRightNoteOutCB.setBounds(crashRightGroup.getX() + 10, crashRightGroup.getY() + 20, crashRightGroup.getWidth() - 20, 30);
    crashRightNoteInCB.setBounds(crashRightGroup.getX() + 10, crashRightGroup.getY() + crashRightGroup.getHeight() - 40, crashRightNoteOutCB.getWidth(), crashRightNoteOutCB.getHeight());

    crashRightSlider.setBounds(
        crashRightNoteOutCB.getX(),
        crashRightNoteOutCB.getY() + crashRightNoteOutCB.getHeight() + 5,
        crashRightNoteInCB.getWidth(),
        crashRightGroup.getHeight() - crashRightNoteInCB.getHeight() - crashRightNoteOutCB.getHeight() - 40
    );

    resetButton.setBounds(WINDOW_WIDTH - 110, WINDOW_HEIGHT - 40, 100, 30);
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &hihatSlider)
        audioProcessor.midiProcessor.hihatVelocity->store(slider->getValue());
    else if (slider == &crashLeftSlider)
        audioProcessor.midiProcessor.crashLeftVelocity->store(slider->getValue());
    else if (slider == &crashRightSlider)
        audioProcessor.midiProcessor.crashRightVelocity->store(slider->getValue());
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::comboBoxChanged(ComboBox* cb) {
    if (cb == &hihatNoteInCB)
        audioProcessor.midiProcessor.hihatNoteIn->store(cb->getSelectedIdAsValue().getValue());
    if (cb == &hihatNoteOutCB)
        audioProcessor.midiProcessor.hihatNoteOut->store(cb->getSelectedIdAsValue().getValue());
    if (cb == &crashLeftNoteInCB)
        audioProcessor.midiProcessor.crashLeftNoteIn->store(cb->getSelectedIdAsValue().getValue());
    if (cb == &crashLeftNoteOutCB)
        audioProcessor.midiProcessor.crashLeftNoteOut->store(cb->getSelectedIdAsValue().getValue());
    if (cb == &crashRightNoteInCB)
        audioProcessor.midiProcessor.crashRightNoteIn->store(cb->getSelectedIdAsValue().getValue());
    if (cb == &crashRightNoteOutCB)
        audioProcessor.midiProcessor.crashRightNoteOut->store(cb->getSelectedIdAsValue().getValue());
}