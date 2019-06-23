#include "utils/concat.h"

// functions
#define channelData		CONCAT2(CHANNEL_ID, ChannelData)
#define nextSample		CONCAT2(CHANNEL_ID, NextSample)


soundChannel channelData;

inline uint16_t nextSample() {
	// Get wave
	uint16_t sample = channelData.sample;
	uint8_t sampleId = ((uint8_t)(sample >> 8)) & SAMPLE_MASK;//channelData.waveFormMask;
	int8_t tone = channelData.waveForm[sampleId];
	#ifdef INTERPOLATE_WAVE
		uint8_t subsampleTone = sample;
		tone += (( channelData.waveForm[sampleId + 1] - tone) * subsampleTone) >> 8;
	#endif
	channelData.sample += channelData.step;

	return tone * channelData.currentVolume;
}



//#define sample		CONCAT2(CHANNEL_ID, Sample)
//#define step		CONCAT2(CHANNEL_ID, Step)
//#define waveForm	CONCAT2(CHANNEL_ID, WaveForm)
//#define currentVolume	CONCAT2(CHANNEL_ID, CurrentVolume)
//
//uint16_t sample;
//uint16_t step;
//const int8_t* waveForm;
//uint8_t currentVolume;
//
//inline uint16_t nextSample() {
//	// Get wave
//	uint16_t asample = sample;
//	uint8_t sampleId = ((uint8_t)(asample >> 8)) & SAMPLE_MASK;//channelData.waveFormMask;
//	int8_t tone = waveForm[sampleId];
//	#ifdef INTERPOLATE_WAVE
//		uint8_t subsampleTone = sample;
//		tone += (( waveForm[sampleId + 1] - tone) * subsampleTone) >> 8;
//	#endif
//	sample += step;
//
//	return tone * currentVolume;
//}
//
//#undef currentVolume
//#undef waveForm
//#undef step
//#undef sample



// undef functions
#undef channelData
#undef nextSample

#undef CHANNEL_ID
