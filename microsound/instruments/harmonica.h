
#include "../microsound.h"
//#include "commonMath.h"

#ifndef INSTRUMENT_NAME
#define INSTRUMENT_NAME harmonica
#endif

#ifndef HARMONICA_SAMPLE
#define HARMONICA_SAMPLE
const int8_t harmonicaSample[SAMPLE_LENGTH + 1] = {
		2, -40 -7, -33, -66, -9, -8, 31,
		68, 62, 76, 65, 26, -38, -75, -33,
		-52, -12, -11, -3, 73, 46, 25, -43,
		-35, -10, -54, -24, -5, 33, 50, 23,
		2}; // last value could be used for interpolation
const int8_t harmonicaVolumeSample[SAMPLE_LENGTH + 1] = {
		0, 113, 107, 98, 90, 82, 76, 69,
		63, 58, 53, 49, 45, 41, 38, 34,
		32, 29, 26, 24, 22, 20, 19, 17,
		16, 14, 13, 12, 11, 10, 9, 8,
		0}; // last value could be used for interpolation
#endif

#include "common/commonInstrument.h"

inline void init() {
	initWaveform(&wave, harmonicaSample, SAMPLE_MASK);
	initWaveform(&volume, harmonicaVolumeSample, SAMPLE_MASK);
}

soundSource play(uint16_t freqStep) {
	resetWaveform(&wave, freqStep);
	resetWaveform(&volume, volumeSampleMillis(100));
	return PPCAT(INSTRUMENT_NAME, NextSample);
}

#include "common/commonInstrumentUndefine.h"
