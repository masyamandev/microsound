
#include "../microsound.h"
#include "common/math.h"

#ifndef INSTRUMENT_NAME
#define INSTRUMENT_NAME piano
#endif

#ifndef PIANO_SAMPLE
#define PIANO_SAMPLE
const int8_t pianoSample[SAMPLE_LENGTH + 1] = {
		0, 41, 78, 106, 122, 126, 117, 98,
		72, 43, 15, -6, -21, -26, -23, -13,
		0, 13, 23, 26, 21, 6, -15, -43,
		-71, -98, -117, -126, -122, -106, -78, -41,
		0}; // last value could be used for interpolation
#endif

#include "common/commonInstrument.h"

inline void init() {
	initWaveform(&wave, pianoSample, SAMPLE_MASK);
	initWaveform(&volume, expNegTable, SAMPLE_MASK);
}

soundSource play(uint16_t freqStep) {
	resetWaveform(&wave, freqStep);
	resetWaveform(&volume, volumeSampleMillis(30));
	return PPCAT(INSTRUMENT_NAME, NextSample);
}

#include "common/commonInstrumentUndefine.h"
