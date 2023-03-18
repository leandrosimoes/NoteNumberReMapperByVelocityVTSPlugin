/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 600;

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
    for (int i = 0; i < 22; i++)
    {
        comboboxesIn[i].addSectionHeading("Note IN");
        comboboxesIn[i].addSeparator();
        comboboxesIn[i].addListener(this);

        for (int j = 0; j <= 128; j++) {
            if (j == 0)
                comboboxesIn[i].addItem("off", j + 1);
            else
                comboboxesIn[i].addItem(std::to_string(j - 1), j + 1);
        }

        addAndMakeVisible(comboboxesIn[i]);

        comboboxInAttatchments[i].reset(new ComboBoxAttatchment(audioProcessor.parameters, "noteIn" + std::to_string(i), comboboxesIn[i]));
    }
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::setupResetButton() {
    resetButton.setButtonText("Reset");
    resetButton.onClick = [this]() {
        for (int i = 0; i < 22; i++)
        {
            comboboxesIn[i].setSelectedId(1);
            comboboxesOut[i].setSelectedId(1);
            sliders[i].setValue(75.0f);
        }
    };

    addAndMakeVisible(resetButton);
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::setupNoteOutCBs() {
    for (int i = 0; i < 22; i++)
    {
        comboboxesOut[i].addSectionHeading("Note Out");
        comboboxesOut[i].addSeparator();
        comboboxesOut[i].addListener(this);

        for (int j = 0; j <= 128; j++) {
            if (j == 0)
                comboboxesOut[i].addItem("off", j + 1);
            else
                comboboxesOut[i].addItem(std::to_string(j - 1), j + 1);
        }

        addAndMakeVisible(comboboxesOut[i]);

        comboboxOutAttatchments[i].reset(new ComboBoxAttatchment(audioProcessor.parameters, "noteOut" + std::to_string(i), comboboxesOut[i]));
    }
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::setupGroups() {
    for (int i = 0; i < 22; i++)
    {
        addAndMakeVisible(groups[i]);
    }
}

 void NoteNumberRemaperByVelocityAudioProcessorEditor::setupSliders() {
     for (int i = 0; i < 22; i++)
     {
         sliders[i].setSliderStyle(Slider::SliderStyle::LinearVertical);
         sliders[i].setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
         sliders[i].setRange(0.0f, 127.0f, 1.0f);
         sliders[i].setValue(70.0f);
         sliders[i].addListener(this);

         addAndMakeVisible(sliders[i]);

         sliderAttatchments[i].reset(new SliderAttachment(audioProcessor.parameters, "slider" + std::to_string(i), sliders[i]));
     }
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

    for (int i = 0; i < 22; i++)
    {
        groups[i].setText(std::to_string(i + 1));

        if (i == 0) {
            groups[i].setBounds(25, titleLabel.getY() + titleLabel.getHeight() + 5, (WINDOW_WIDTH - 100) / 11, (WINDOW_HEIGHT - 100) / 2);
            comboboxesOut[i].setBounds(groups[i].getX() + 10, groups[i].getY() + 15, groups[i].getWidth() - 20, 30);
        }
        else if (i > 0 && i < 11) {
            groups[i].setBounds(groups[i - 1].getX() + groups[i - 1].getWidth() + 5, titleLabel.getY() + titleLabel.getHeight() + 5, groups[i - 1].getWidth(), groups[i - 1].getHeight());
            comboboxesOut[i].setBounds(groups[i].getX() + 10, groups[i].getY() + 15, comboboxesOut[i - 1].getWidth(), comboboxesOut[i - 1].getHeight());
        }
        else if (i == 11) {
            groups[i].setBounds(25, titleLabel.getY() + titleLabel.getHeight() + 5 + groups[i - 1].getHeight() + 5, groups[i - 1].getWidth(), groups[i - 1].getHeight());
            comboboxesOut[i].setBounds(groups[i].getX() + 10, groups[i].getY() + 15, comboboxesOut[i - 1].getWidth(), comboboxesOut[i - 1].getHeight());
        }
        else if (i > 0 && i >= 11) {
            groups[i].setBounds(groups[i - 1].getX() + groups[i - 1].getWidth() + 5, titleLabel.getY() + titleLabel.getHeight() + 5 + groups[i - 1].getHeight() + 5, groups[i - 1].getWidth(), groups[i - 1].getHeight());
            comboboxesOut[i].setBounds(groups[i].getX() + 10, groups[i].getY() + 15, comboboxesOut[i - 1].getWidth(), comboboxesOut[i - 1].getHeight());
        }

        sliders[i].setBounds(comboboxesOut[i].getX(), comboboxesOut[i].getY() + comboboxesOut[i].getHeight() + 5, groups[i].getWidth() - 20, groups[i].getHeight() - 95);
        comboboxesIn[i].setBounds(comboboxesOut[i].getX(), sliders[i].getY() + sliders[i].getHeight() + 5, comboboxesOut[i].getWidth(), comboboxesOut[i].getHeight());
    }

    resetButton.setBounds(groups[21].getX(), groups[21].getY() + groups[21].getHeight() + 5, groups[21].getWidth(), 30);
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    for (int i = 0; i < 22; i++)
    {
        if (slider == &sliders[i])
            audioProcessor.midiProcessor.velocities[i]->store(slider->getValue());
    }
}

void NoteNumberRemaperByVelocityAudioProcessorEditor::comboBoxChanged(ComboBox* cb) {
    for (int i = 0; i < 22; i++)
    {
        if (cb == &comboboxesIn[i])
            audioProcessor.midiProcessor.notesIn[i]->store(cb->getSelectedIdAsValue().getValue());

        if (cb == &comboboxesOut[i])
            audioProcessor.midiProcessor.notesOut[i]->store(cb->getSelectedIdAsValue().getValue());
    }
}