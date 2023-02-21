#pragma once

#include "JuceHeader.h"

using namespace juce;

constexpr int HIHAT_DEFAULT_NOTE_NUMBER_IN = 8;
constexpr int HIHAT_DEFAULT_NOTE_NUMBER_OUT = 7;
constexpr int HIHAT_DEFAULT_VELOCITY_BREAK_POINT = 70;

constexpr int CRASH_LEFT_DEFAULT_NOTE_NUMBER_IN = 8;
constexpr int CRASH_LEFT_DEFAULT_NOTE_NUMBER_OUT = 7;
constexpr int CRASH_LEFT_DEFAULT_VELOCITY_BREAK_POINT = 70;

constexpr int CRASH_RIGHT_DEFAULT_NOTE_NUMBER_IN = 8;
constexpr int CRASH_RIGHT_DEFAULT_NOTE_NUMBER_OUT = 7;
constexpr int CRASH_RIGHT_DEFAULT_VELOCITY_BREAK_POINT = 70;

class MidiProcessor
{
public:
	void process(MidiBuffer& midiMessages)
	{
		processedBuffer.clear();

		MidiBuffer::Iterator it(midiMessages);
		MidiMessage currentMessage;
		int samplePos;

		while (it.getNextEvent(currentMessage, samplePos)) {
			if (currentMessage.isNoteOnOrOff()) {
				auto& transposedMessage = currentMessage;

				if (currentMessage.getNoteNumber() == HIHAT_DEFAULT_NOTE_NUMBER_IN) {
					if (currentMessage.getVelocity() > HIHAT_DEFAULT_VELOCITY_BREAK_POINT)
						transposedMessage.setNoteNumber(HIHAT_DEFAULT_NOTE_NUMBER_OUT);
				}

				if (currentMessage.getNoteNumber() == CRASH_LEFT_DEFAULT_NOTE_NUMBER_IN) {
					if (currentMessage.getVelocity() > CRASH_LEFT_DEFAULT_VELOCITY_BREAK_POINT)
						transposedMessage.setNoteNumber(CRASH_LEFT_DEFAULT_NOTE_NUMBER_OUT);
				}

				if (currentMessage.getNoteNumber() == CRASH_RIGHT_DEFAULT_NOTE_NUMBER_IN) {
					if (currentMessage.getVelocity() > CRASH_RIGHT_DEFAULT_VELOCITY_BREAK_POINT)
						transposedMessage.setNoteNumber(CRASH_RIGHT_DEFAULT_NOTE_NUMBER_OUT);
				}

				processedBuffer.addEvent(transposedMessage, samplePos);
			}
			else {
				processedBuffer.addEvent(currentMessage, samplePos);
			}
		}

		midiMessages.swapWith(processedBuffer);
	};

	MidiBuffer processedBuffer;
};
