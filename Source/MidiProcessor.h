#pragma once

#include "JuceHeader.h"

using namespace juce;

constexpr int HIHAT_DEFAULT_NOTE_NUMBER_IN = 8;
constexpr int HIHAT_DEFAULT_NOTE_NUMBER_OUT = 7;

constexpr int CRASH_LEFT_DEFAULT_NOTE_NUMBER_IN = 49;
constexpr int CRASH_LEFT_DEFAULT_NOTE_NUMBER_OUT = 48;

constexpr int CRASH_RIGHT_DEFAULT_NOTE_NUMBER_IN = 57;
constexpr int CRASH_RIGHT_DEFAULT_NOTE_NUMBER_OUT = 56;

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

		if (currentNote == HIHAT_DEFAULT_NOTE_NUMBER_IN && currentVelocity > hihatVelocity) {
			return currentMessage.setNoteNumber(HIHAT_DEFAULT_NOTE_NUMBER_OUT);
		}

		if (currentNote == CRASH_LEFT_DEFAULT_NOTE_NUMBER_IN && currentVelocity > crashLeftVelocity) {
			return currentMessage.setNoteNumber(CRASH_LEFT_DEFAULT_NOTE_NUMBER_OUT);
		}

		if (currentNote == CRASH_RIGHT_DEFAULT_NOTE_NUMBER_IN && currentVelocity > crashRightVelocity) {
			return currentMessage.setNoteNumber(CRASH_RIGHT_DEFAULT_NOTE_NUMBER_OUT);
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

	double hihatVelocity;
	double crashLeftVelocity;
	double crashRightVelocity;

	MidiBuffer processedBuffer;
};
