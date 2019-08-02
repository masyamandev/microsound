
#ifndef MICROSOUND_FREQUENCY_DIVIDER
#define MICROSOUND_FREQUENCY_DIVIDER	1 // 2^n
#endif

#include "../microsound.h"

#include "../globalSoundInterpolation.h"

inline void initSound() {
	// prescale timer to 1/1st the clock rate
	TCCR0 |= (1<<CS00);
	// enable timer overflow interrupt
	TIMSK |= (1<<TOIE1);

	// Init PWM on timer1
	TCCR1A=(1<<COM1A1)|(1<<WGM10); // Fast PWM
	TCCR1B=(1<<CS10)|(1<<WGM12);

	// Set PB1 as output
	DDRB |= 0x02;

	resetSound();
}

// Timer interrupt
ISR(TIMER1_OVF_vect) {
#if (MICROSOUND_FREQUENCY_DIVIDER > 1) && ((!defined INTERPOLATION_STRENGTH) || (INTERPOLATION_STRENGTH == 0))
	static uint8_t microsampleSampleSkipCounter;
	if ((microsampleSampleSkipCounter++) & (MICROSOUND_FREQUENCY_DIVIDER - 1)) {
		return;
	}
#endif
	OCR1AL = sampleToUint8(getNextInterpolatedSample());
}