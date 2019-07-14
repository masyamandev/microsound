
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
	TCCR1A=(1<<COM1A0)|(1<<PWM1A); // Fast PWM
	TCCR1B=(1<<CS10);

	TCNT1 = 0x00;
	OCR1A = 127;
	OCR1C = 0xFF;

	// Init timer 0 interrupts
	TCCR0 = (1<<CS00);

	TIMSK = (1<<TOIE0);

	// Set PB1 as output (pin2)
	DDRB = 0xFF;//0x02;

	resetSound();
}


uint8_t cnt;
// Timer0 interrupt
ISR(TIMER0_OVF0_vect) {
#if (MICROSOUND_FREQUENCY_DIVIDER > 1) && ((!defined INTERPOLATION_STRENGTH) || (INTERPOLATION_STRENGTH == 0))
	if ((cnt++) & (MICROSOUND_FREQUENCY_DIVIDER - 1)) {
		return;
	}
#endif
	OCR1A = sampleToUint8(getNextInterpolatedSample());
}
