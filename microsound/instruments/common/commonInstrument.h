
#ifndef PPCAT
#define PPCAT_NX(A, B) A ## B
#define PPCAT(A, B) PPCAT_NX(A, B)
#endif

// functions
#define nextSample	PPCAT(INSTRUMENT_NAME, NextSample)
#define init		PPCAT(INSTRUMENT_NAME, Init)
#define play		INSTRUMENT_NAME

// vars
#define wave	PPCAT(INSTRUMENT_NAME, Wave)
#define volume	PPCAT(INSTRUMENT_NAME, Volume)

waveform wave, volume;

#ifndef CUSTOM_VOICE

//int8_t nextSample() {
//	return (getNextValue(&wave) * getNextVolume(&volume)) >> 8;
//}

int8_t nextSample() {
	// Get volume
	uint16_t sample = volume.sample;
	uint8_t sampleId = sample >> 8;
	if (sampleId > volume.waveFormMask) {
		return 0;
	}
	int8_t vol = volume.waveForm[sampleId];
#ifdef INTERPOLATE_VOLUME
	uint8_t subsampleVol = sample;
	vol += ((volume.waveForm[sampleId + 1] - vol) * subsampleVol) >> 8;
#endif
	if (!downsampleCounter) {
		volume.sample += volume.step;
	}

	// Get wave
	sample = wave.sample;
	sampleId = ((uint8_t)(sample >> 8)) & wave.waveFormMask;
	int8_t tone = wave.waveForm[sampleId];
#ifdef INTERPOLATE_WAVE
	uint8_t subsampleTone = sample;
	tone += ((wave.waveForm[sampleId + 1] - tone) * subsampleTone) >> 8;
#endif
	wave.sample += wave.step;

	// Combine tone and volume
	return vol * tone >> 8;
}

#endif
