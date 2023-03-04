#pragma once

#include "JuceHeader.h"

using namespace juce;

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
		auto hihatVelocityValue = hihatVelocity->load();
		auto crashLeftVelocityValue = crashLeftVelocity->load();
		auto crashRightVelocityValue = crashRightVelocity->load();
		auto hihatNoteInValue = hihatNoteIn->load() - 1;
		auto hihatNoteOutValue = hihatNoteOut->load() - 1;
		auto crashLeftNoteInValue = crashLeftNoteIn->load() - 1;
		auto crashLeftNoteOutValue = crashLeftNoteOut->load() - 1;
		auto crashRightNoteInValue = crashRightNoteIn->load() - 1;
		auto crashRightNoteOutValue = crashRightNoteOut->load() - 1;

		if (currentNote == hihatNoteInValue && currentVelocity <= roundFloatToInt(hihatVelocityValue)) {
			currentMessage.setNoteNumber(hihatNoteOutValue);
		}

		if (currentNote == crashLeftNoteInValue && currentVelocity <= roundFloatToInt(crashLeftVelocityValue)) {
			currentMessage.setNoteNumber(crashLeftNoteOutValue);
		}

		if (currentNote == crashRightNoteInValue && currentVelocity <= roundFloatToInt(crashRightVelocityValue)) {
			currentMessage.setNoteNumber(crashRightNoteOutValue);
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
		hihatVelocity = new std::atomic<float>(75.0f);
		crashLeftVelocity = new std::atomic<float>(80.0f);
		crashRightVelocity = new std::atomic<float>(80.0f);

		hihatNoteIn = new std::atomic<int>(9);
		hihatNoteOut = new std::atomic<int>(8);

		crashLeftNoteIn = new std::atomic<int>(50);
		crashLeftNoteOut = new std::atomic<int>(49);

		crashRightNoteIn = new std::atomic<int>(58);
		crashRightNoteOut = new std::atomic<int>(57);
	}

	std::atomic<float>* hihatVelocity = nullptr;
	std::atomic<float>* crashLeftVelocity = nullptr;
	std::atomic<float>* crashRightVelocity = nullptr;

	std::atomic<int>* hihatNoteIn = nullptr;
	std::atomic<int>* hihatNoteOut = nullptr;

	std::atomic<int>* crashLeftNoteIn = nullptr;
	std::atomic<int>* crashLeftNoteOut = nullptr;

	std::atomic<int>* crashRightNoteIn = nullptr;
	std::atomic<int>* crashRightNoteOut = nullptr;

	MidiBuffer processedBuffer;
};
