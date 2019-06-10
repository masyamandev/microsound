
#ifndef MICROSOUND_INIT
#define MICROSOUND_INIT

#ifndef VOICE_COUNTER
#define VOICE_COUNTER	1
#endif

#ifndef MICROSOUND_FREQUENCY
#define MICROSOUND_FREQUENCY 		(F_CPU / 256 / MICROSOUND_FREQUENCY_DIVIDER) // PCM sample rate
#endif

#ifndef VOLUME_CHANGE_DOWNSAMPLING
#define VOLUME_CHANGE_DOWNSAMPLING	128 // MICROSOUND_FREQUENCY / 256 rounded to 2^n
#endif
#define VOLUME_CHANGE_DOWNSAMPLING_MASK	(VOLUME_CHANGE_DOWNSAMPLING - 1)

//#define volumeSampleMillis(millis)	((uint16_t) (1000L * MICROSOUND_FREQUENCY / 256 / VOLUME_CHANGE_DOWNSAMPLING / (millis)))
#define volumeSampleMillis(millis)	((uint16_t) (1000L * 256 * VOLUME_CHANGE_DOWNSAMPLING / MICROSOUND_FREQUENCY / (millis)))

#define fromBpm(beatsPerMinute)		((uint16_t) (60L * MICROSOUND_FREQUENCY / (beatsPerMinute)))

uint16_t bpmIncrementAt;
uint16_t sampleCounter;
uint16_t beatCounter;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 8
#endif

#define BUFFER_MASK (BUFFER_SIZE - 1)
volatile uint8_t soundBuffer[BUFFER_SIZE];
volatile uint8_t bufferRead;
uint8_t bufferWrite;

uint8_t downsampleCounter;


#include "frequencies.h"
#include "waveform.h"
//#include "volumeform.h"


typedef int8_t (*soundSource)();

soundSource channels[VOICE_COUNTER];
uint8_t volumes[VOICE_COUNTER];

int8_t silence() {
	return 0;
}

inline void playSound(uint8_t channel, soundSource sound, uint8_t volume) {
	channels[channel] = sound;
	volumes[channel] = volume;
}

inline void resetSound() {
	sampleCounter = 0;
	beatCounter = 0;

	int i;
	for (i = 0; i < VOICE_COUNTER; i++) {
		channels[i] = silence;
		volumes[i] = 128;
	}
}

uint8_t getNextSample() {

	if ((sampleCounter--) == 0) {
		sampleCounter = bpmIncrementAt;
		beatCounter++;
	}

	downsampleCounter = (downsampleCounter + 1) & VOLUME_CHANGE_DOWNSAMPLING_MASK;

	uint16_t val = 0x8000;

	int i;
	for (i = 0; i < VOICE_COUNTER; i++) {
		val += channels[i]() * volumes[i];
	}

	return val >> 8;
}

inline void fillBuffer() {
	while (bufferWrite != bufferRead) {
		soundBuffer[bufferWrite] = getNextSample();
		bufferWrite = (bufferWrite + 1) & BUFFER_MASK;
	}
}

#endif
