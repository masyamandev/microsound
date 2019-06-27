
#include "instruments/common/semirandom.h"

const uint8_t* noiseVolume;
uint8_t noiseFramesRemain;
uint8_t prevBeatTickCounter;
uint8_t noiseCurrentVolume;
uint8_t noiseDataVolume;

inline void resetNoise() {
	noiseFramesRemain = 0;
}

inline void playNoise(const uint8_t* noiseData, uint8_t dataLength, uint8_t volume) {
	noiseVolume = noiseData;
	noiseFramesRemain = dataLength;
	noiseDataVolume = volume;
	noiseCurrentVolume = (*noiseData * volume) >> 8;
}

inline int16_t noiseNextSample() {


	if (beatTickCounter != prevBeatTickCounter) {
		prevBeatTickCounter = beatTickCounter;
		noiseFramesRemain--;
		noiseCurrentVolume = (pgm_read_byte(noiseVolume++) * noiseCurrentVolume) >> 8;
	}

	if (noiseFramesRemain == 0) {
		noiseCurrentVolume = 0; // TODO move up and return
//		return 0;
	}

//	if (!(tickSampleCounter & 0x3)) {
		nextSemirandom();
//	}

	return ((int8_t)semirandomValue) * noiseCurrentVolume;
}
