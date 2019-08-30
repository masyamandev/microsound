/*
 * 16 bits PWM driver for ATmega48/88/168/328p.
 * It uses two PWM output pins which should be mixed in proportion 1/256.
 *
 * It uses timer1 both for PWM and overflow interrupt.
 *
 * Sample rate is F_CPU / 256 which is equal to 31250 Hz for 8MHz clock or 62500 Hz for 16MHz clock.
 * Sample rate can be lowered by 2, 4 or 8 by using MICROSOUND_FREQUENCY_DIVIDER.
 * Lowered sample rate can be extrapolated back to it's original frequency using
 * INTERPOLATION_STRENGTH values 1, 2 or 3 accordingly.
 *
 * This implementation does not support custom sample rates.
 *
 * Output pins are PB1 (high), PB2 (low).
 * Resistor connected to PB2 should have 256 times higher resistance comparing to resistor connected to PB1.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

#ifndef BUFFER_BITS
#define BUFFER_BITS 16
#endif

#ifndef MICROSOUND_FREQUENCY_DIVIDER
#define MICROSOUND_FREQUENCY_DIVIDER	1 // 2^n
#endif

#include "../microsound.h"

#include "../globalSoundInterpolation.h"

inline void initSound() {
	// Enable timer overflow interrupt
	TIMSK1 |= (1<<TOIE1);

	// Init PWM on timer1
	TCCR1A=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM10); // Fast PWM
	TCCR1B=(1<<CS10)|(1<<WGM12);

	// Set PB1 and PB2 as output
	DDRB |= 0x02 | 0x04;

	resetSound();
}

// Timer interrupt
ISR(TIMER1_OVF_vect) {
#include "common/skipSamples.h"
	uint16_t output = sampleToUint16(getNextInterpolatedSample());
	OCR1AL = output >> 8;
	OCR1BL = output & 0xFF;
}
