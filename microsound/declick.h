/*
 * Experimental piece of code which eliminates clicks when playing of wave sample is interrupted by new note.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

#ifdef ENABLE_DECLICK

uint8_t currentZeroSampleValue;

inline uint16_t getZeroSample() {
	return currentZeroSampleValue << 8;
}

inline void addToZeroSampleValue(int16_t value) {
	currentZeroSampleValue += (value >> 8);
}

inline void addChannelToZeroSample(waveChannel* channelData) {
	// Get wave
	uint16_t sample = channelData->waveSample;
	uint8_t sampleId = ((uint8_t)(sample >> 8)) & SAMPLE_MASK;
	int8_t tone = pgm_read_byte(&channelData->waveForm[sampleId]);

	addToZeroSampleValue(mulSignedUnsigned(tone, channelData->currentVolume));
}


inline void moveToZeroSampleValue() {
	if (currentZeroSampleValue > 0x80) {
		currentZeroSampleValue--;
	} else if (currentZeroSampleValue < 0x80) {
		currentZeroSampleValue++;
	}

//#define DECLICK_STRENGTH	8
//	if (currentZeroSampleValue > 0x80 + DECLICK_STRENGTH - 1) {
//		currentZeroSampleValue -= DECLICK_STRENGTH;
//	} else if (currentZeroSampleValue < 0x80 - DECLICK_STRENGTH + 1) {
//		currentZeroSampleValue += DECLICK_STRENGTH;
//	}
}

#else

#define getZeroSample()		0x8000
//#define addToZeroSampleValue(value)
#define addChannelToZeroSample(channelData)
#define moveToZeroSampleValue()

#endif
