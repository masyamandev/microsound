#ifndef MICROMUSIC_DALAY_INIT
#define MICROMUSIC_DALAY_INIT

/*
 * Control delays using function  similar to <util/delay.h>.
 * During delay sound buffer is filled with sound data.
 *
 * Currently delay is not too accurate, especially with small values.
 * It's recommended to use delays in range [0.2 ... 1000] milliseconds. If longer delays are needed it's possible
 * to use 32 bits sample counter:
 * #define DELAY_SAMPLE_COUNTER_TYPE	uint32_t
 */


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

	while (1) {
		fillBuffer((samples > SAMPLES_PER_TICK) ? SAMPLES_PER_TICK : samples);

		uint8_t samplesPassed = bufferReadCounter - prevSampleCounter;
		prevSampleCounter += samplesPassed;

		noUpdatesCounter -= (uint8_t) samplesPassed;
		// Overflow, too long time passed since last buffer update
		if (noUpdatesCounter >= SAMPLES_PER_TICK) {
			updateMusicData();
			noUpdatesCounter = SAMPLES_PER_TICK - 1;
		}

		if (samplesPassed >= samples) {
			return;
		}
		samples -= samplesPassed;
	}
}


#endif
