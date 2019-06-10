
typedef struct
{
	uint16_t sample;
	uint16_t step;
	const int8_t* waveForm;
	uint8_t waveFormMask;
} waveform;


int8_t getNextValue(waveform *wave) {

	uint16_t sample = wave->sample;

	uint8_t sampleId = ((uint8_t)(sample >> 8)) & wave->waveFormMask;

	int8_t val = wave->waveForm[sampleId];

#ifdef INTERPOLATE_WAVE
	uint8_t subsample = sample;
	val += ((wave->waveForm[sampleId + 1] - val) * subsample) >> 8;
#endif

	wave->sample += wave->step;

	return val;
}

int8_t getNextVolume(waveform *wave) {

	uint16_t sample = wave->sample;

	uint8_t sampleId = sample >> 8;
	if (sampleId > wave->waveFormMask) {
		return 0;
	}

	int8_t val = wave->waveForm[sampleId];
#ifdef INTERPOLATE_VOLUME
	uint8_t subsample = sample;
	val += ((wave->waveForm[sampleId + 1] - val) * subsample) >> 8;
#endif

	if (!downsampleCounter) {
		wave->sample += wave->step;
	}

	return val;

//	return 127;
}


inline void resetWaveform(waveform *wave, uint16_t step) {
	wave->sample = 0;
	wave->step = step;
}

inline void initWaveform(waveform *wave, const int8_t* waveForm, uint8_t waveFormMask) {
	wave->waveForm = waveForm;
	wave->waveFormMask = waveFormMask;
	resetWaveform(wave, 0);
}
