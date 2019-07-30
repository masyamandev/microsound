
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

	DDRB = 0xFF;//0x08 | 0x04 | 0x02 | 0x01;

	resetSound();
}


uint8_t cnt;
// Timer interrupt
ISR(TIMER2_OVF_vect) {
//ISR(TIMER0_OVF_vect) {
#if (MICROSOUND_FREQUENCY_DIVIDER > 1) && ((!defined INTERPOLATION_STRENGTH) || (INTERPOLATION_STRENGTH == 0))
	if ((cnt++) & (MICROSOUND_FREQUENCY_DIVIDER - 1)) {
		return;
	}
#endif
	OCR2 = sampleToUint8(getNextInterpolatedSample());
}
