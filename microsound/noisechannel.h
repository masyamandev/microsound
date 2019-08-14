/*
 * Noise channel.
 * Generates noise with specific volume changed over time.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "instruments/common/semirandom.h"

// Update noise value every 2 ^ NOISE_UPDATE_SAMPLES_SKIP samples
#ifndef NOISE_UPDATE_SAMPLES_SKIP
#define NOISE_UPDATE_SAMPLES_SKIP	0
#endif

const uint8_t* noiseVolume;
uint8_t noiseFramesRemain;
uint8_t noiseCurrentVolume;
uint8_t noiseDataVolume;
uint8_t toNextVolumeCounter;

inline void resetNoise() {
	noiseFramesRemain = 0;
}

inline void playNoise(const uint8_t* noiseData, uint8_t dataLength, uint8_t volume) {
	noiseVolume = noiseData;
	noiseFramesRemain = dataLength + 1;
	noiseDataVolume = volume;
	toNextVolumeCounter = 0;
}

inline int16_t noiseNextSample() {

	if (noiseFramesRemain == 0) {
#ifndef NOISE_CALCULATION_WHEN_UNUSED // Useful for speed debug
		return 0;
#else
		noiseCurrentVolume = 0;
		toNextVolumeCounter++; // Avoid next if statement to become true
#endif
	}

	if (!(toNextVolumeCounter--)) {
		toNextVolumeCounter = SAMPLES_PER_TICK;
		noiseFramesRemain--;
		noiseCurrentVolume = mulUnsigned8bits(pgm_read_byte(noiseVolume++), noiseDataVolume);
	}


	if (!(tickSampleCounter & ((1 << NOISE_UPDATE_SAMPLES_SKIP) - 1))) {
		nextSemirandom();
	}

	return mulSignedUnsigned((int8_t)semirandomValue, noiseCurrentVolume);
}
