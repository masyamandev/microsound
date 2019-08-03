#ifndef MICROMUSIC_DALAY_INIT
#define MICROMUSIC_DALAY_INIT

#include "micromusic.h"


// For delays longer than 1 second use uint32_t
#ifndef DELAY_SAMPLE_COUNTER_TYPE
#define DELAY_SAMPLE_COUNTER_TYPE	uint16_t
#endif

// Init function similar to <util/delay.h>
#ifndef MANUAL_DELAY_INIT
#define _delay_ms(ms)	delaySamples((DELAY_SAMPLE_COUNTER_TYPE) ((ms) * (MICROSOUND_FREQUENCY) / 1000))
#endif

//void delaySamples8bits(uint8_t samples) {
//	fillBuffer(samples);
//	updateMusicData();
//}

static uint8_t noUpdatesCounter;

void delaySamples(DELAY_SAMPLE_COUNTER_TYPE samples) {
	uint8_t prevSampleCounter = bufferReadCounter;

	// Checking high byte only can cause delay in update music, up to 255 samples.
	while (samples >> 8) {
		fillBuffer(SAMPLES_PER_TICK);

		updateMusicData();
		noUpdatesCounter = SAMPLES_PER_TICK;

		uint8_t samplesPassed = bufferReadCounter - prevSampleCounter;
		prevSampleCounter += samplesPassed;
		samples -= (DELAY_SAMPLE_COUNTER_TYPE) samplesPassed;
	}
	fillBuffer(samples);

	noUpdatesCounter -= samples;
	// Overflow, too long time passed since last buffer update
	if (noUpdatesCounter > SAMPLES_PER_TICK) {
		updateMusicData();
		noUpdatesCounter = SAMPLES_PER_TICK;
	}
}


#endif
