/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoteNumberRemaperByVelocityAudioProcessor::NoteNumberRemaperByVelocityAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                        parameters(*this, nullptr, juce::Identifier("NoteNumberRemaperByVelocityAudioProcessor"),
                        {
                            std::make_unique<juce::AudioParameterFloat>("hihatVelocity", "HihatVelocity", 0.0f, 127.0f, 75.0f),
                            std::make_unique<juce::AudioParameterFloat>("crashLeftVelocity", "CrashLeftVelocity", 0.0f, 127.0f, 80.0f),
                            std::make_unique<juce::AudioParameterFloat>("crashRightVelocity", "CrashRightVelocity", 0.0f, 127.0f, 80.0f),
                            std::make_unique<juce::AudioParameterInt>("hihatNoteIn", "HihatNoteIn", 1, 128, 9),
                            std::make_unique<juce::AudioParameterInt>("hihatNoteOut", "HihatNoteOut", 1, 128, 8),
                            std::make_unique<juce::AudioParameterInt>("crashLeftNoteIn", "CrashLeftNoteIn", 1, 128, 50),
                            std::make_unique<juce::AudioParameterInt>("crashLeftNoteOut", "CrashLeftNoteOut", 1, 128, 49),
                            std::make_unique<juce::AudioParameterInt>("crashRightNoteIn", "CrashRightNoteIn", 1, 128, 58),
                            std::make_unique<juce::AudioParameterInt>("crashRightNoteOut", "CrashRightNoteOut", 1, 128, 57)
                        })
#endif
{
    midiProcessor.setDefaultValues();
}

NoteNumberRemaperByVelocityAudioProcessor::~NoteNumberRemaperByVelocityAudioProcessor()
{
}

//==============================================================================
const juce::String NoteNumberRemaperByVelocityAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoteNumberRemaperByVelocityAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoteNumberRemaperByVelocityAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NoteNumberRemaperByVelocityAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NoteNumberRemaperByVelocityAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoteNumberRemaperByVelocityAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NoteNumberRemaperByVelocityAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NoteNumberRemaperByVelocityAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NoteNumberRemaperByVelocityAudioProcessor::getProgramName (int index)
{
    return {};
}

void NoteNumberRemaperByVelocityAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NoteNumberRemaperByVelocityAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NoteNumberRemaperByVelocityAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NoteNumberRemaperByVelocityAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NoteNumberRemaperByVelocityAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    midiProcessor.process(midiMessages);
}

//==============================================================================
bool NoteNumberRemaperByVelocityAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NoteNumberRemaperByVelocityAudioProcessor::createEditor()
{
    return new NoteNumberRemaperByVelocityAudioProcessorEditor (*this);
}

//==============================================================================
void NoteNumberRemaperByVelocityAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void NoteNumberRemaperByVelocityAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr) {
        if (xmlState->hasTagName(parameters.state.getType())) {
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));

            midiProcessor.hihatVelocity = parameters.getRawParameterValue("hihatVelocity");
            midiProcessor.crashLeftVelocity = parameters.getRawParameterValue("crashLeftVelocity");
            midiProcessor.crashRightVelocity = parameters.getRawParameterValue("crashRightVelocity");

            midiProcessor.hihatNoteIn->store(roundFloatToInt(parameters.getRawParameterValue("hihatNoteIn")->load()));
            midiProcessor.hihatNoteOut->store(roundFloatToInt(parameters.getRawParameterValue("hihatNoteOut")->load()));

            midiProcessor.crashLeftNoteIn->store(roundFloatToInt(parameters.getRawParameterValue("crashLeftNoteIn")->load()));
            midiProcessor.crashLeftNoteOut->store(roundFloatToInt(parameters.getRawParameterValue("crashLeftNoteOut")->load()));

            midiProcessor.crashRightNoteIn->store(roundFloatToInt(parameters.getRawParameterValue("crashRightNoteIn")->load()));
            midiProcessor.crashRightNoteOut->store(roundFloatToInt(parameters.getRawParameterValue("crashRightNoteOut")->load()));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoteNumberRemaperByVelocityAudioProcessor();
}
