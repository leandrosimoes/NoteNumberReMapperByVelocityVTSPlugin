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

		// Keep track of the maximum velocity for the current note
		// This ensure to get the most appropriate note if there 
		// are multiple notes set with the same note number but with different velocities
		float higherVelocityFound = 0.0f;
		
		int finalNoteOut = -1;

		for (int i = 0; i < 22; i++)
		{
			int currentNoteIn = (notesIn[i]->load() - 2);
			int currentNoteOut = (notesOut[i]->load() - 2);

			if (currentNoteIn < 0 || currentNoteOut < 0) continue;

			float currentVelocity = roundFloatToInt(velocities[i]->load());

			if (currentNoteIn == currentNotePlayed && currentVelocityPlayed >= currentVelocity && currentVelocity >= higherVelocityFound) {
				higherVelocityFound = currentVelocity;
				finalNoteOut = currentNoteOut;
			}
		}

		if (finalNoteOut > -1)
			currentMessage.setNoteNumber(finalNoteOut);

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
