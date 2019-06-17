
#include "../microsound.h"
#include "common/math.h"

#ifndef INSTRUMENT_NAME
#define INSTRUMENT_NAME percussion
#endif

//#define CUSTOM_VOICE
#include "common/commonInstrument.h"

soundSource play(uint8_t note) {
	resetWaveform(&wave, frequency(note));
	resetWaveform(&volume, volumeSampleMillis(5));
	return nextSample;
}

inline sampleSource init() {
	initWaveform(&wave, noise, SAMPLE_MASK);
	initWaveform(&volume, expNegTable, SAMPLE_MASK);
	return play;
}

//int8_t nextSample() {
//	// Get volume
//	uint16_t sample = volume.sample;
//	uint8_t sampleId = sample >> 8;
//	if (sampleId > volume.waveFormMask) {
//		return 0;
//	}
//	int8_t vol = volume.waveForm[sampleId];
//#ifdef INTERPOLATE_VOLUME
//	uint8_t subsampleVol = sample;
//	vol += ((volume.waveForm[sampleId + 1] - vol) * subsampleVol) >> 8;
//#endif
//	if (!downsampleCounter) {
//		volume.sample += volume.step;
//	}
//
//	// Get wave
//	sample = wave.sample;
//	sampleId = ((uint8_t)(sample >> 8)) & wave.waveFormMask;
//	int8_t tone = wave.waveForm[sampleId];
//#ifdef INTERPOLATE_WAVE
//	uint8_t subsampleTone = sample;
//	tone += ((wave.waveForm[sampleId + 1] - tone) * subsampleTone) >> 8;
//#endif
//	wave.sample += wave.step;
//
//	// Combine tone and volume
//	return vol * tone >> 8;
//}

#include "common/commonInstrumentUndefine.h"
