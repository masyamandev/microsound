/*
 * 8 bits PWM driver for ATtiny261/461/861.
 *
 * It uses timer1 for high frequency PWM and timer0 for overflow interrupt.
 *
 * This implementation supports custom sample rates. Interrupt frequency will be
 * calculated according to MICROSOUND_FREQUENCY.
 *
 * Output pin is PB3.
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "../microsound.h"

#include "../globalSoundInterpolation.h"

inline void initSound() {

	// Enable PLL for timer 1
	PLLCSR = (1 << PLLE);
	while (!(PLLCSR & (1<<PLOCK)));
	PLLCSR |= (1 << PCKE);

	// Init timer 1 fast PWM
    TCCR1A =
            (1<<PWM1B)	|
    		(1<<COM1B1);
    TCCR1B =
    		(1<<(CS10));

	TCNT1 = 0x00;
	OCR1B = 127;
//	OCR1C = 0xFF;

	// Init timer 0 interrupts
	TCCR0B = (1<<CS01);
	TCCR0A = (1<<CTC0);
	OCR0A = (F_CPU / 8 / MICROSOUND_FREQUENCY);

	TIMSK = (1<<OCIE0A);

	// Set PB3 as output (pin4)
	DDRB |= 0x08;

	resetSound();
}


// Timer0 interrupt
ISR(TIMER0_COMPA_vect) {
	OCR1B = sampleToUint8(getNextInterpolatedSample());
}
