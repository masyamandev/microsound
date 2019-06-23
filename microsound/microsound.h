
#ifndef MICROSOUND_INIT
#define MICROSOUND_INIT

#ifndef CHANNELS_SIZE
#define CHANNELS_SIZE	1
#endif

#ifndef MICROSOUND_FREQUENCY_DIVIDER
#define MICROSOUND_FREQUENCY_DIVIDER	1
#endif

#ifndef MICROSOUND_FREQUENCY
#define MICROSOUND_FREQUENCY 		(F_CPU / 256 / MICROSOUND_FREQUENCY_DIVIDER) // PCM sample rate
#endif

// 1 tick = 4ms. 8-bit divider of frequency should handle up to 65kHz (up to 16MHz CPU). 8-bit multiplier can handle up to 1 second.
#define TICKS_PER_SECOND	250
#define SAMPLES_PER_TICK	(MICROSOUND_FREQUENCY / TICKS_PER_SECOND) // TODO fmin(MICROSOUND_FREQUENCY / TICKS_PER_SECOND, 255)

#ifndef VOLUME_CHANGE_DOWNSAMPLING
#define VOLUME_CHANGE_DOWNSAMPLING	128 // MICROSOUND_FREQUENCY / 256 rounded to 2^n
#endif
#define VOLUME_CHANGE_DOWNSAMPLING_MASK	(VOLUME_CHANGE_DOWNSAMPLING - 1)

//#define volumeSampleMillis(millis)	((uint16_t) (1000L * MICROSOUND_FREQUENCY / 256 / VOLUME_CHANGE_DOWNSAMPLING / (millis)))
#define volumeSampleMillis(millis)	((uint16_t) (1000L * 256 * VOLUME_CHANGE_DOWNSAMPLING / MICROSOUND_FREQUENCY / (millis)))

// Support up to 1 beat per second
#define fromBpm(beatsPerMinute)		(60L * TICKS_PER_SECOND / (beatsPerMinute)) // TODO fmin((60L * TICKS_PER_SECOND / (beatsPerMinute)), 255)

uint8_t tickSampleCounter;
uint8_t beatTickCounter;
uint8_t beatIncrementAt;
uint16_t beatCounter;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 8
#endif

#define BUFFER_MASK (BUFFER_SIZE - 1)
volatile uint8_t soundBuffer[BUFFER_SIZE];
volatile uint8_t bufferRead;
uint8_t bufferWrite;


#include "frequencies.h"


typedef struct
{
	// Info about wave
	uint16_t sample;
	uint16_t step;
	const int8_t* waveForm;
//	uint8_t waveFormMask;

	// Info about volume
	uint8_t currentVolume;
	uint8_t instrumentVolume;

} soundChannel;

//soundChannel channels[CHANNELS_SIZE];
//
//inline void setVolume(uint8_t channel, uint8_t volume) {
//	channels[channel].instrumentVolume = volume;
//}


#define CHANNEL_ID	channel1
#include "wavechannel.h"
#define CHANNEL_ID	channel2
#include "wavechannel.h"
#define CHANNEL_ID	channel3
#include "wavechannel.h"
#define CHANNEL_ID	channel4
#include "wavechannel.h"
//#define CHANNEL_ID	channel5
//#include "wavechannel.h"
//#define CHANNEL_ID	channel6
//#include "wavechannel.h"
//#define CHANNEL_ID	channel7
//#include "wavechannel.h"
//#define CHANNEL_ID	channel8
//#include "wavechannel.h"


inline void setBpm(uint8_t counter) {
	beatIncrementAt = counter;
	beatTickCounter = counter;
}

inline void resetChannel(soundChannel* channel) {
	channel->sample = 0;
	channel->step = 0;
	channel->currentVolume = 0;
	channel->instrumentVolume = 128;

//	channel->waveForm = sinTable;
//	channel->waveFormMask = SAMPLE_MASK;
}

inline void resetSound() {
	beatTickCounter = beatIncrementAt;
	beatCounter = 0;

//	uint8_t i;
//	for (i = 0; i < CHANNELS_SIZE; i++) {
//		channels[i].sample = 0;
//		channels[i].step = 0;
//		channels[i].currentVolume = 128;
//		channels[i].instrumentVolume = 128;
//	}

	resetChannel(&channel1ChannelData);
	resetChannel(&channel2ChannelData);
	resetChannel(&channel3ChannelData);
	resetChannel(&channel4ChannelData);
//	resetChannel(&channel5ChannelData);
//	resetChannel(&channel6ChannelData);
//	resetChannel(&channel7ChannelData);
//	resetChannel(&channel8ChannelData);
}

inline uint8_t getNextSample() {

	if ((tickSampleCounter--) == 0) {
		tickSampleCounter = SAMPLES_PER_TICK;
		if ((beatTickCounter--) == 0) {
			beatTickCounter = beatIncrementAt;
			beatCounter++;
		}
	}

//	if ((sampleCounter--) == 0) {
//		sampleCounter = bpmIncrementAt;
//		beatCounter++;
//	}
//	downsampleCounter = (downsampleCounter + 1) & VOLUME_CHANGE_DOWNSAMPLING_MASK;

	uint16_t val = 0x8000;
//	int i;
//	for (i = CHANNELS_SIZE - 1; i >= 0; i--) {
//
//		// Get wave
//		uint16_t sample = channels[i].sample;
//		uint8_t sampleId = ((uint8_t)(sample >> 8)) & channels[i].waveFormMask;
//		int8_t tone = channels[i].waveForm[sampleId];
//		#ifdef INTERPOLATE_WAVE
//			uint8_t subsampleTone = sample;
//			tone += (( channels[i].waveForm[sampleId + 1] - tone) * subsampleTone) >> 8;
//		#endif
//		channels[i].sample += channels[i].step;
//
//		val +=
//			#ifdef DECLICK
//				channels[i].prevValue =
//			#endif
//				tone * channels[i].currentVolume;
//	}
//
//	#ifdef DECLICK
//		declickValue -= (int8_t) declickValue >> 8;
//		val += declickValue;
//	#endif

	val += channel1NextSample();
	val += channel2NextSample();
	val += channel3NextSample();
	val += channel4NextSample();
//	val += channel5NextSample();
//	val += channel6NextSample();
//	val += channel7NextSample();
//	val += channel8NextSample();

	return val >> 8;

}

#include "globalSoundInterpolation.h"

inline void fillBuffer() {
	while (bufferWrite != bufferRead) {
		soundBuffer[bufferWrite] = getNextInterpolatedSample();
		bufferWrite = (bufferWrite + 1) & BUFFER_MASK;
	}

//	uint8_t toWrite = (bufferRead - bufferWrite) & BUFFER_MASK;
//	for (; toWrite > 0; toWrite--) {
//		soundBuffer[bufferWrite] = getNextInterpolatedSample();
//		bufferWrite = (bufferWrite + 1) & BUFFER_MASK;
//	}
}

#endif
