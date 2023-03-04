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

    titleLabel.setText("Note Number Remaper By Velocity", juce::dontSendNotification);
    titleLabel.setJustificationType(Justification::centred);

    addAndMakeVisible(titleLabel);

    setupGroups();
    setupNoteInCBs();
    setupSliders();
    setupNoteOutCBs();
    setupResetButton();
 }

void NoteNumberRemaperByVelocityAudioProcessorEditor::setupNoteInCBs() {
    // HIHAT
    hihatNoteInCB.addSectionHeading("Note IN");
    hihatNoteInCB.addSeparator();
    hihatNoteInCB.addListener(this);

    // CRASH LEFT
    crashLeftNoteInCB.addSectionHeading("Note IN");
    crashLeftNoteInCB.addSeparator();
    crashLeftNoteInCB.addListener(this);

    // CRASH RIGHT
    crashRightNoteInCB.addSectionHeading("Note IN");
    crashRightNoteInCB.addSeparator();
    crashRightNoteInCB.addListener(this);

    hihatNoteInCB.addItem("8", 9);
    crashLeftNoteInCB.addItem("49", 50);
    crashRightNoteInCB.addItem("57", 58);

    // ADDING ITEMS TO ALL CBS
    /*for (int i = 0; i <= 127; i++) {
        hihatNoteInCB.addItem(std::to_string(i), i + 1);
        crashLeftNoteInCB.addItem(std::to_string(i), i + 1);
        crashRightNoteInCB.addItem(std::to_string(i), i + 1);
    }*/

    // MAKING ALL CBS VISIBLE
    addAndMakeVisible(hihatNoteInCB);
    addAndMakeVisible(crashLeftNoteInCB);
    addAndMakeVisible(crashRightNoteInCB);

    // ATTATCHING ALL CBS
    hihatNoteInCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "hihatNoteIn", hihatNoteInCB));
    crashLeftNoteInCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "crashLeftNoteIn", crashLeftNoteInCB));
    crashRightNoteInCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "crashRightNoteIn", crashRightNoteInCB));
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::setupResetButton() {
    resetButton.setButtonText("Reset");
    resetButton.onClick = [this]() {
        hihatNoteInCB.setSelectedId(9);
        hihatNoteOutCB.setSelectedId(8);
        crashLeftNoteInCB.setSelectedId(50);
        crashLeftNoteOutCB.setSelectedId(49);
        crashRightNoteInCB.setSelectedId(58);
        crashRightNoteOutCB.setSelectedId(57);

        hihatSlider.setValue(75.0f);
        crashLeftSlider.setValue(85.0f);
        crashRightSlider.setValue(85.0f);
    };

    addAndMakeVisible(resetButton);
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::setupNoteOutCBs() {
    // HIHAT
    hihatNoteOutCB.addSectionHeading("Note OUT");
    hihatNoteOutCB.addSeparator();
    hihatNoteOutCB.addListener(this);

    // CRASH LEFT
    crashLeftNoteOutCB.addSectionHeading("Note OUT");
    crashLeftNoteOutCB.addSeparator();
    crashLeftNoteOutCB.addListener(this);

    // CRASH RIGHT
    crashRightNoteOutCB.addSectionHeading("Note OUT");
    crashRightNoteOutCB.addSeparator();
    crashRightNoteOutCB.addListener(this);

    // ADDING ITEMS TO ALL CBS
    for (int i = 0; i <= 127; i++) {
        if (i == 8 || i == 49 || i == 57) continue;

        hihatNoteOutCB.addItem(std::to_string(i), i + 1);
        crashLeftNoteOutCB.addItem(std::to_string(i), i + 1);
        crashRightNoteOutCB.addItem(std::to_string(i), i + 1);
    }

    // MAKING ALL CBS VISIBLE
    addAndMakeVisible(hihatNoteOutCB);
    addAndMakeVisible(crashLeftNoteOutCB);
    addAndMakeVisible(crashRightNoteOutCB);

    // ATTATCHING ALL CBS
    hihatNoteOutCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "hihatNoteOut", hihatNoteOutCB));
    crashLeftNoteOutCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "crashLeftNoteOut", crashLeftNoteOutCB));
    crashRightNoteOutCBAttachment.reset(new ComboBoxAttatchment(audioProcessor.parameters, "crashRightNoteOut", crashRightNoteOutCB));
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::setupGroups() {
    // HIHAT
    hihatGroup.setText("HiHat");
    hihatGroup.setTextLabelPosition(Justification::centredTop);

    // CRASH LEFT
    crashLeftGroup.setText("Crash Left");
    crashLeftGroup.setTextLabelPosition(Justification::centredTop);

    // CRASH RIGHT
    crashRightGroup.setText("Crash Right");
    crashRightGroup.setTextLabelPosition(Justification::centredTop);

    addAndMakeVisible(hihatGroup);
    addAndMakeVisible(crashLeftGroup);
    addAndMakeVisible(crashRightGroup);
}

 void NoteNumberRemaperByVelocityAudioProcessorEditor::setupSliders() {
     // HIHAT
     hihatSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
     hihatSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
     hihatSlider.setRange(0.0f, 127.0f, 1.0f);
     hihatSlider.setValue(70.0f);
     hihatSlider.addListener(this);

     // CRASH LEFT
     crashLeftSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
     crashLeftSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
     crashLeftSlider.setRange(0.0f, 127.0f, 1.0f);
     crashLeftSlider.setValue(70.0f);
     crashLeftSlider.addListener(this);

     // CRASH RIGHT
     crashRightSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
     crashRightSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
     crashRightSlider.setRange(0.0f, 127.0f, 1.0f);
     crashRightSlider.setValue(70.0f);
     crashRightSlider.addListener(this);

     addAndMakeVisible(hihatSlider);
     addAndMakeVisible(crashLeftSlider);
     addAndMakeVisible(crashRightSlider);

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
    auto currentValue = slider->getValue();

    if (slider == &hihatSlider)
        audioProcessor.midiProcessor.hihatVelocity->store(currentValue);
    else if (slider == &crashLeftSlider)
        audioProcessor.midiProcessor.crashLeftVelocity->store(currentValue);
    else if (slider == &crashRightSlider)
        audioProcessor.midiProcessor.crashRightVelocity->store(currentValue);
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::comboBoxChanged(ComboBox* cb) {
    auto currentValue = cb->getSelectedIdAsValue().getValue();

    if (cb == &hihatNoteInCB)
        audioProcessor.midiProcessor.hihatNoteIn->store(currentValue);
    if (cb == &hihatNoteOutCB)
        audioProcessor.midiProcessor.hihatNoteOut->store(currentValue);
    if (cb == &crashLeftNoteInCB)
        audioProcessor.midiProcessor.crashLeftNoteIn->store(currentValue);
    if (cb == &crashLeftNoteOutCB)
        audioProcessor.midiProcessor.crashLeftNoteOut->store(currentValue);
    if (cb == &crashRightNoteInCB)
        audioProcessor.midiProcessor.crashRightNoteIn->store(currentValue);
    if (cb == &crashRightNoteOutCB)
        audioProcessor.midiProcessor.crashRightNoteOut->store(currentValue);
}