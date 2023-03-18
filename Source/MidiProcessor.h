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
		auto currentNotePlayed = currentMessage.getNoteNumber();
		auto currentVelocityPlayed = currentMessage.getVelocity();

		for (int i = 0; i < 22; i++)
		{
			int currentNoteIn = (notesIn[i]->load() - 2);
			float currentVelocity = roundFloatToInt(velocities[i]->load());

			if (currentNoteIn >= 0 && currentNoteIn == currentNotePlayed && currentVelocityPlayed <= currentVelocity)
				currentMessage.setNoteNumber((notesOut[i]->load() - 2));
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
