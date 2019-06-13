
#ifndef MICROSOUND_INIT
#define MICROSOUND_INIT

#ifndef VOICE_COUNTER
#define VOICE_COUNTER	1
#endif

#ifndef MICROSOUND_FREQUENCY_DIVIDER
#define MICROSOUND_FREQUENCY_DIVIDER	1
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

uint16_t declickValue;


#include "frequencies.h"
#include "waveform.h"
//#include "volumeform.h"


typedef int8_t (*soundSource)();

typedef soundSource (*sampleSource)(uint8_t);


typedef struct
{
	soundSource sound;
	uint8_t volume;
#ifdef DECLICK
	uint16_t prevValue;
#endif
} soundChannel;

soundChannel channels[VOICE_COUNTER];

int8_t silence() {
	return 0;
}

inline void setVolume(uint8_t channel, uint8_t volume) {
	channels[channel].volume = volume;
}

inline void playSound(uint8_t channel, soundSource sound) {
#ifdef DECLICK
	declickValue += channels[channel].prevValue;
	channels[channel].prevValue = 0;
#endif
	channels[channel].sound = sound;
}

inline void setBpm(uint16_t counter) {
	bpmIncrementAt = counter;
	sampleCounter = counter;
}

inline void resetSound() {
	sampleCounter = bpmIncrementAt;
	beatCounter = 0;

	int i;
	for (i = 0; i < VOICE_COUNTER; i++) {
		channels[i].sound = silence;
		channels[i].volume = 128;
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
		val +=
#ifdef DECLICK
				channels[i].prevValue =
#endif
				channels[i].sound() * channels[i].volume;
	}

#ifdef DECLICK
	declickValue -= (int8_t) declickValue >> 8;
	val += declickValue;
#endif

	return val >> 8;
}

#if INTERPOLATION_STRENGTH > 1
uint8_t interpolationCounter;
uint16_t interpolationValue, interpolationDiff;
inline uint8_t getNextInterpolatedSample() {
	interpolationCounter = (interpolationCounter + 1) & ((1 << INTERPOLATION_STRENGTH) - 1);
	if (!interpolationCounter) {
		uint16_t next = getNextSample() << 8;
		interpolationDiff = ((int16_t)(next - interpolationValue)) >> INTERPOLATION_STRENGTH;
	}
	interpolationValue += interpolationDiff;
	return interpolationValue >> 8;
}
#endif

inline void fillBuffer() {
	while (bufferWrite != bufferRead) {
#if INTERPOLATION_STRENGTH > 1
		soundBuffer[bufferWrite] = getNextInterpolatedSample();
#else
		soundBuffer[bufferWrite] = getNextSample();
#endif
		bufferWrite = (bufferWrite + 1) & BUFFER_MASK;
	}
}

#endif
