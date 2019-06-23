#include "utils/concat.h"

// functions
#define channelData		CONCAT2(CHANNEL_ID, ChannelData)
#define nextSample		CONCAT2(CHANNEL_ID, NextSample)


soundChannel channelData;

inline uint16_t nextSample() {
	// Get wave
	uint16_t sample = channelData.waveSample;
	uint8_t sampleId = ((uint8_t)(sample >> 8)) & SAMPLE_MASK;
	int8_t tone = pgm_read_byte(&channelData.waveForm[sampleId]);
	#ifdef INTERPOLATE_WAVE
		uint8_t subsampleTone = sample;
		tone += (( pgm_read_byte(&channelData.waveForm[sampleId + 1]) - tone) * subsampleTone) >> 8;
	#endif
	channelData.waveSample += channelData.waveStep;

	return tone * channelData.currentVolume;
}


// undef functions
#undef channelData
#undef nextSample

#undef CHANNEL_ID
