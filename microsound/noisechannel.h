
#include "instruments/common/semirandom.h"

// In 4ms ticks
#ifndef NOISE_BUFFER_SIZE
#define NOISE_BUFFER_SIZE	16 // 2^n
#define NOISE_BUFFER_MASK	(NOISE_BUFFER_SIZE - 1)
#endif

uint8_t noiseVolume[NOISE_BUFFER_SIZE];
uint8_t noiseFrame;
uint8_t prevBeatTickCounter;
uint8_t noiseCurrentVolume;

inline void resetNoise() {
	noiseFrame = 0;
	uint8_t i;
	for (i = 0; i < NOISE_BUFFER_SIZE; i++) {
		noiseVolume[i] = 0;
	}
}

inline void playNoise(uint8_t* noiseData, uint8_t dataLength, uint8_t volume) {
	uint8_t i;
	for (i = 0; i < dataLength; i++) {
		noiseVolume[i & NOISE_BUFFER_MASK] += (*(noiseData++) * volume) >> 8;
	}
}

inline int16_t noiseNextSample() {
	if (beatTickCounter != prevBeatTickCounter) {
		prevBeatTickCounter = beatTickCounter;
		noiseVolume[noiseFrame] = 0;
		noiseFrame = (noiseFrame + 1) & NOISE_BUFFER_MASK;
		noiseCurrentVolume = noiseVolume[noiseFrame];
	}

//	if (!(tickSampleCounter & 0x3)) {
		nextSemirandom();
//	}

	return ((int8_t)semirandomValue) * noiseCurrentVolume;
}
