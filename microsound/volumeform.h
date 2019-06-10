
// TEST FILE

typedef struct
{
	const int8_t* waveForm;
	uint8_t waveFormMask;
	uint16_t cnt, limit;
	uint8_t subsample, increment;
	uint8_t index;
	int16_t val, diff;
} volumeform;

//int8_t getNextVolume1(volumeform *wave) {
//
//	if ((wave->cnt--) == 0) {
//		wave->cnt = wave->limit;
//
//		wave->subsample += wave->increment;
//		if (wave->subsample < wave->increment) {
//			wave->index++;
//			wave->index &= wave->waveFormMask;
//			wave->val = wave->waveForm[wave->index];
//			wave->diff = wave->waveForm[wave->index + 1] - wave->val;
//		}
//	}
//
////	int8_t interpolate = ((b - a) * subsample) >> 8;
////	int8_t val = a;// + interpolate;
////
////	if (moveToNextSample) {
////		wave->sample += wave->step;
////	}
//
//	return wave->val;
//
////	return 127;
//}

inline void recalculateVolDiff(volumeform *wave, uint8_t index) {
	int16_t diff = (wave->waveForm[index] << 8) - wave->val;
	wave->diff = diff / wave->limit;
}

int8_t getNextVolume1(volumeform *wave) {

	if ((wave->cnt--) == 0) {
		wave->cnt = wave->limit;

//		wave->subsample += wave->increment;
		wave->index = (wave->index + 1 ) & wave->waveFormMask;
		recalculateVolDiff(wave, wave->index);
	}

	wave->val += -1;//wave->diff;
//	int8_t interpolate = ((b - a) * subsample) >> 8;
//	int8_t val = a;// + interpolate;
//
//	if (moveToNextSample) {
//		wave->sample += wave->step;
//	}

	return wave->val >> 8;

//	return 127;
}

inline void resetVol(volumeform *wave, uint16_t step) {
	wave->cnt = 0;
	wave->limit = step;
	wave->index = 0;
	wave->subsample = 0xFF;

	wave->val = wave->waveForm[0] << 8;
	recalculateVolDiff(wave, 1);
}

inline void initVol(volumeform *wave, int8_t* waveForm, uint8_t waveFormMask) {
	wave->waveForm = waveForm;
	wave->waveFormMask = waveFormMask;
	wave->increment = 1;
	resetVol(wave, 0);
}

