
// TEST FILE

#include "../microsound.h"
#include "commonMath.h"

#ifndef INSTRUMENT_NAME
#define INSTRUMENT_NAME piano
#endif

#include "commonInstrument.h"

#ifndef PIANO_SAMPLE
#define PIANO_SAMPLE
const int8_t pianoSample[SAMPLE_LENGTH + 1] = {
		0, 41, 78, 106, 122, 126, 117, 98,
		72, 43, 15, -6, -21, -26, -23, -13,
		0, 13, 23, 26, 21, 6, -15, -43,
		-71, -98, -117, -126, -122, -106, -78, -41,
		0}; // last value could be used for interpolation
#endif

#define wave	PPCAT(INSTRUMENT_NAME, Wave)
#define wave1	PPCAT(INSTRUMENT_NAME, Wave1)
#define volume	PPCAT(INSTRUMENT_NAME, Volume)

waveform wave, volume;
waveform wave1;

inline void PPCAT(INSTRUMENT_NAME, Init)() {
	initWaveform(&wave, pianoSample, SAMPLE_MASK);
	initWaveform(&wave1, sinTable, SAMPLE_MASK);
	initWaveform(&volume, expNegTable, SAMPLE_MASK);
}

int8_t PPCAT(INSTRUMENT_NAME, NextSample)() {
	return ((getNextValue(&wave) + getNextValue(&wave1)) * getNextVolume(&volume)) >> 8;
//	return (getNextValue(&wave) * getNextVolume(&volume)) >> 8;
}

soundSource INSTRUMENT_NAME(uint16_t freqStep) {
	resetWaveform(&wave, freqStep);
	resetWaveform(&wave1, freqStep * 2);
	resetWaveform(&volume, volumeSampleMillis(30));
	return PPCAT(INSTRUMENT_NAME, NextSample);
}

#undef wave
#undef wave1
#undef volume
#undef INSTRUMENT_NAME
