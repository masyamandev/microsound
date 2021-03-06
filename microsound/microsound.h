
#ifndef MICROSOUND_INIT
#define MICROSOUND_INIT

/*
 * Generates multi-channel sound.
 *
 * Generated sound contains of several wave channels and optionally single noise channel.
 * Wave channel is a repeated wave of specified form and it's volume changed over time.
 * Noise channel is a randomized values changing it's volume over time.
 *
 * All channels are mixed up according to channel volumes.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

// Amount of wave channels
#ifndef CHANNELS_SIZE
#define CHANNELS_SIZE	1
#endif

#if CHANNELS_SIZE > 8
#warning "Currently maximum amount of channels is 8"
#endif

// Divide default PCM sample rate onto this value
#ifndef MICROSOUND_FREQUENCY_DIVIDER
#define MICROSOUND_FREQUENCY_DIVIDER	1
#endif

// Default PCM sample rate onto this value. May have issues if sample rate > 65k.
#ifndef MICROSOUND_FREQUENCY
#define MICROSOUND_FREQUENCY 		(F_CPU / 256 / MICROSOUND_FREQUENCY_DIVIDER) // PCM sample rate
#endif

#define toByteConstant(x)	((x >= 255) ? 255 : ((uint8_t) (x)))

// 1 tick = 4ms. 8-bit divider of frequency should handle up to 65kHz (up to 16MHz CPU). 8-bit multiplier can handle up to 1 second.
#define TICKS_PER_SECOND	250
#define SAMPLES_PER_TICK	toByteConstant(MICROSOUND_FREQUENCY / TICKS_PER_SECOND)

#if (MICROSOUND_FREQUENCY / TICKS_PER_SECOND >= 255)
#warning "Sampling frequency is too high. It should be lower than 65kHz. Incorrect timings are possible."
#endif

// Support up to 1 beat per second
#define fromBpm(beatsPerMinute)		toByteConstant(60L * TICKS_PER_SECOND / (beatsPerMinute))

// Control code inlining. To inline use `#define INLINE_... inline`
#ifndef INLINE_BUFFER_FILL
#define INLINE_BUFFER_FILL /* do not inline  by default */
#endif
#ifndef INLINE_SOUND_CONTROL
#define INLINE_SOUND_CONTROL /* do not inline by default */
#endif


uint8_t tickSampleCounter;
uint8_t beatTickCounter;
uint8_t beatIncrementAt;
uint16_t beatCounter;

uint8_t volumeRecalculationId;

typedef struct
{
	// Info about wave
	const int8_t* waveForm; // Wave table array
	uint16_t waveSample; // High byte is an index in waveForm array
	uint16_t waveStep; // Frequency, how waveSample is changed in time

	// Info about volume envelope
	const uint8_t* volumeForm; // Array of volume change in time
	uint8_t volumeFormLength; // Length of volumeForm
	uint8_t volumeTicksPerSample; // How many ticks should pass before index of volumeForm is changed
	uint8_t volumeTicksCounter; // Counter for volumeTicksPerSample

	// Info about volume
	uint8_t currentVolume; // Precalculated volume for current tick
	uint8_t instrumentVolume; // Volume of channel
} waveChannel;

waveChannel* channels[CHANNELS_SIZE];

#include "../utils/multiply.h"
#include "buffer.h"
#include "frequencies.h"
#include "declick.h"
#include "instruments/common/commonWave.h"

// Set volume for specified wave channel
inline void setVolume(uint8_t channel, uint8_t volume) {
	channels[channel]->instrumentVolume = volume;
}

// Add noise channel
#ifdef USE_NOISE_CHANNEL
	#include "noisechannel.h"
#endif
// Add wave channels
#if CHANNELS_SIZE >= 1
	#define CHANNEL_ID	channel0
	#include "wavechannel.h"
#endif
#if CHANNELS_SIZE >= 2
	#define CHANNEL_ID	channel1
	#include "wavechannel.h"
#endif
#if CHANNELS_SIZE >= 3
	#define CHANNEL_ID	channel2
	#include "wavechannel.h"
#endif
#if CHANNELS_SIZE >= 4
	#define CHANNEL_ID	channel3
	#include "wavechannel.h"
#endif
#if CHANNELS_SIZE >= 5
	#define CHANNEL_ID	channel4
	#include "wavechannel.h"
#endif
#if CHANNELS_SIZE >= 6
	#define CHANNEL_ID	channel5
	#include "wavechannel.h"
#endif
#if CHANNELS_SIZE >= 7
	#define CHANNEL_ID	channel6
	#include "wavechannel.h"
#endif
#if CHANNELS_SIZE >= 8
	#define CHANNEL_ID	channel7
	#include "wavechannel.h"
#endif


// Set beats per minute value. For example:
// setBpm(fromBpm(180));
// will increment beatCounter 180 times per minute or 3 times per second.
inline void setBpm(uint8_t counter) {
	beatIncrementAt = counter;
	beatTickCounter = counter;
}

// Clean data for wave channel
inline void resetChannel(waveChannel* channel) {
	channel->waveSample = 0;
	channel->waveStep = 0;
	channel->volumeFormLength = 0;
	channel->volumeTicksCounter = channel->volumeTicksPerSample;
	channel->currentVolume = 0;
	channel->instrumentVolume = 0;
}

// Clean data for all channels
void resetSound() {
	setBpm(fromBpm(60)); // Avoid too high BPM at MCU start
	beatCounter = 0;

	#if CHANNELS_SIZE >= 1
		channels[0] = &channel0ChannelData;
	#endif
	#if CHANNELS_SIZE >= 2
		channels[1] = &channel1ChannelData;
	#endif
	#if CHANNELS_SIZE >= 3
		channels[2] = &channel2ChannelData;
	#endif
	#if CHANNELS_SIZE >= 4
		channels[3] = &channel3ChannelData;
	#endif
	#if CHANNELS_SIZE >= 5
		channels[4] = &channel4ChannelData;
	#endif
	#if CHANNELS_SIZE >= 6
		channels[5] = &channel5ChannelData;
	#endif
	#if CHANNELS_SIZE >= 7
		channels[6] = &channel6ChannelData;
	#endif
	#if CHANNELS_SIZE >= 8
		channels[7] = &channel7ChannelData;
	#endif

	uint8_t i;
	for (i = 0; i < CHANNELS_SIZE; i++) {
		resetChannel(channels[i]);
	}

	#ifdef USE_NOISE_CHANNEL
		resetNoise();
	#endif
}

// Recalculate volume for a channel
inline void recalculateVolume(waveChannel* channel) {

	if ((channel->volumeTicksCounter--) == 0 && channel->volumeFormLength > 0) {
		channel->volumeTicksCounter = channel->volumeTicksPerSample;
		channel->volumeFormLength--;
		channel->volumeForm++;
	}

#ifdef MICROSOUND_STATIC_VOLUME
	channel->currentVolume = (pgm_read_byte(channel->volumeForm)) >> MICROSOUND_STATIC_VOLUME;
#else
	channel->currentVolume = mulUnsigned8bits(pgm_read_byte(channel->volumeForm), channel->instrumentVolume);
#endif

}


// Calculate next sample on all channels
inline soundSample getNextSample() {

	if ((tickSampleCounter--) == 0) {
		tickSampleCounter = SAMPLES_PER_TICK - 1;
		if ((beatTickCounter--) == 0) {
			beatTickCounter = beatIncrementAt;
			beatCounter++;
		}
	}

	// volume recalculation should no be done so often for all channels
	if (tickSampleCounter < CHANNELS_SIZE) {
		recalculateVolume(channels[tickSampleCounter]);
	}

	uint16_t val = getZeroSample(); // Optional declick code


	#ifdef USE_NOISE_CHANNEL
		val += noiseNextSample();
	#endif

	#if CHANNELS_SIZE >= 1
		val += channel0NextSample();
	#endif
	#if CHANNELS_SIZE >= 2
		val += channel1NextSample();
	#endif
	#if CHANNELS_SIZE >= 3
		val += channel2NextSample();
	#endif
	#if CHANNELS_SIZE >= 4
		val += channel3NextSample();
	#endif
	#if CHANNELS_SIZE >= 5
		val += channel4NextSample();
	#endif
	#if CHANNELS_SIZE >= 6
		val += channel5NextSample();
	#endif
	#if CHANNELS_SIZE >= 7
		val += channel6NextSample();
	#endif
	#if CHANNELS_SIZE >= 8
		val += channel7NextSample();
	#endif


	return toSample(val);

}

// Fill buffer until maxSamples is read or buffer is full. May cause bugs if maxSamples is too close to 255.
INLINE_BUFFER_FILL
void fillBuffer(uint8_t maxSamples) {
	uint8_t sampleCounterAtStart = bufferReadCounter;

	// Less code but slower
//	while (1) {
//		uint8_t currentCounter = bufferReadCounter;
//		if (((uint8_t)(currentCounter - sampleCounterAtStart)) > maxSamples || (currentCounter & BUFFER_MASK) == bufferWrite) {
//			return;
//		}
//		writeToBuffer(getNextSample());
//	}

	uint8_t limit = maxSamples;
	uint8_t currentCounter = sampleCounterAtStart;
	while ((currentCounter & BUFFER_MASK) != bufferWrite) {
		writeToBuffer(getNextSample());
		currentCounter = bufferReadCounter;

		if (!(--limit)) {
			limit = currentCounter - sampleCounterAtStart;
			if (limit > maxSamples) { // overflow
				moveToZeroSampleValue(); // Optional declick code
				return;
			}
		}
	}
}

#endif
