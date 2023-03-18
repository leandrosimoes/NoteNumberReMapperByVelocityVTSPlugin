#pragma once

#include "JuceHeader.h"

using namespace juce;

class MidiProcessor {
private:
	void processMessages(MidiBuffer midiMessages) {
		MidiBuffer::Iterator it(midiMessages);
		MidiMessage currentMessage;
		int samplePos;

		while (it.getNextEvent(currentMessage, samplePos)) {
			if (currentMessage.isNoteOnOrOff())
				remapNote(currentMessage, samplePos);
			else
				processedBuffer.addEvent(currentMessage, samplePos);
		}
	}

	void remapNote(MidiMessage currentMessage, int samplePos) {
		auto currentNote = currentMessage.getNoteNumber();
		auto currentVelocity = currentMessage.getVelocity();

		int index = -1;

		for (int i = 0; i < 22; i++)
		{
			if ((notesIn[i]->load() - 1) == currentNote && currentVelocity <= roundFloatToInt(velocities[i]->load()))
				currentMessage.setNoteNumber(notesOut[i]->load() - 1);
		}

		processedBuffer.addEvent(currentMessage, samplePos);
	}
	
public:
	void process(MidiBuffer& midiMessages) {
		processedBuffer.clear();

		if (!midiMessages.isEmpty()) {
			processMessages(midiMessages);
			midiMessages.swapWith(processedBuffer);
		}
	};

	void setDefaultValues() {
		for (int i = 0; i < 22; i++)
		{
			velocities[i] = new std::atomic<float>(75.0f);
			notesIn[i] = new std::atomic<int>(0);
			notesOut[i] = new std::atomic<int>(0);
		}
	}

	std::atomic<float>* velocities[22];
	std::atomic<int>* notesIn[22];
	std::atomic<int>* notesOut[22];

	MidiBuffer processedBuffer;
};
