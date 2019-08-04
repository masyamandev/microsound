/*
 * 8 bits PWM driver for AtMega8.
 *
 * It uses timer2 both for PWM and overflow interrupt.
 *
 * Sample rate is F_CPU / 256 which is equal to 31250 Hz for 8MHz clock or 62500 Hz for 16MHz clock.
 * Sample rate can be lowered by 2, 4 or 8 by using MICROSOUND_FREQUENCY_DIVIDER.
 * Lowered sample rate can be extrapolated back to it's original frequency using
 * INTERPOLATION_STRENGTH values 1, 2 or 3 accordingly.
 *
 * This implementation does not support custom sample rates.
 *
 * Output pin is PB3.
 */

#ifndef MICROSOUND_FREQUENCY_DIVIDER
#define MICROSOUND_FREQUENCY_DIVIDER	1 // 2^n
#endif

#include "../microsound.h"

#include "../globalSoundInterpolation.h"

inline void initSound() {
	// prescale timer to 1/1st the clock rate
	TCCR0 |= (1<<CS00);
	// enable timer overflow interrupt
	TIMSK |= (1<<TOIE2);

	// Init PWM on timer2
	TCCR2=(1<<WGM21)|(1<<WGM20)|(1<<CS20)|(1<<COM21); // Fast PWM

	// Set PB3 as output
	DDRB |= 0x08;

	resetSound();
}

// Timer interrupt
ISR(TIMER2_OVF_vect) {
#if (MICROSOUND_FREQUENCY_DIVIDER > 1) && ((!defined INTERPOLATION_STRENGTH) || (INTERPOLATION_STRENGTH == 0))
	static uint8_t microsampleSampleSkipCounter;
	if ((microsampleSampleSkipCounter++) & (MICROSOUND_FREQUENCY_DIVIDER - 1)) {
		return;
	}
#endif
	OCR2 = sampleToUint8(getNextInterpolatedSample());
}
