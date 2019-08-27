/*
 * 8 bits PWM driver for ATtiny26.
 *
 * It uses timer1 for high frequency PWM and timer0 for overflow interrupt.
 *
 * Sample rate is F_CPU / 256 which is equal to 31250 Hz for 8MHz clock or 62500 Hz for 16MHz clock.
 * Sample rate can be lowered by 2, 4 or 8 by using MICROSOUND_FREQUENCY_DIVIDER.
 * Lowered sample rate can be extrapolated back to it's original frequency using
 * INTERPOLATION_STRENGTH values 1, 2 or 3 accordingly.
 *
 * This implementation does not support custom sample rates.
 *
 * Output pin is PB3.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

#ifndef MICROSOUND_FREQUENCY_DIVIDER
#define MICROSOUND_FREQUENCY_DIVIDER	1 // 2^n
#endif

#include "../microsound.h"

#include "../globalSoundInterpolation.h"

inline void initSound() {

	// Enable PLL for timer 1
	PLLCSR = (1 << PLLE);
	while (!(PLLCSR & (1<<PLOCK)));
	PLLCSR |= (1 << PCKE);

	// Init timer 1 fast PWM
	TCCR1A=(1<<COM1B0)|(1<<PWM1B); // Fast PWM
	TCCR1B=(1<<CS10);

	TCNT1 = 0x00;
	OCR1B = 127;
	OCR1C = 0xFF;

	// Init timer 0 interrupts
	TCCR0 = (1<<CS00);

	TIMSK = (1<<TOIE0);

	// Set PB3 as output (pin4)
	DDRB |= 0x08;

	resetSound();
}


uint8_t cnt;
// Timer0 interrupt
ISR(TIMER0_OVF0_vect) {
#include "common/skipSamples.h"
	OCR1B = sampleToUint8(getNextInterpolatedSample());
}
