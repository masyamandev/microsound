
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
    TCCR1 =
            (1<<CTC1)    | // Enable PWM
            (1<<PWM1A)   | // Set source to pck
            (1<<(CS10))  | // Clear the pin when match with ocr1x
            (1<<COM1A1);
    GTCCR =   (1<<PWM1B) | (1<<COM1B1);

	TCNT1 = 0x00;
	OCR1A = 127;
	OCR1C = 0xFF;

	// Init timer 0 interrupts
	TCCR0B = (1<<CS00);

	TIMSK = (1<<TOIE0);

	// Set PB1 as output (pin2)
	DDRB = 0xFF;//0x02;

	resetSound();
}


uint8_t cnt;
// Timer0 interrupt
ISR(TIMER0_OVF_vect) {
#if (MICROSOUND_FREQUENCY_DIVIDER > 1) && ((!defined INTERPOLATION_STRENGTH) || (INTERPOLATION_STRENGTH == 0))
	if ((cnt++) & (MICROSOUND_FREQUENCY_DIVIDER - 1)) {
		return;
	}
#endif
	OCR1A = sampleToUint8(getNextInterpolatedSample());
}
