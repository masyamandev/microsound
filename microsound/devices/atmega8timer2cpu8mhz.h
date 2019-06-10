
#ifndef MICROSOUND_FREQUENCY_DIVIDER
#define MICROSOUND_FREQUENCY_DIVIDER	1 // 2^n
#endif

#include "../microsound.h"



inline void initSound() {
	// prescale timer to 1/1st the clock rate
	TCCR0 |= (1<<CS00);
	// prescale timer to 1/8th the clock rate
//	TCCR0 |= (1<<CS01);
	// enable timer overflow interrupt
	TIMSK |= (1<<TOIE2);
//	TIMSK |= (1<<TOIE0);


	// Init PWM on timer1
	TCCR1A=(1<<COM1A1)|(1<<WGM10); // Fast PWM
	TCCR1B=(1<<CS10)|(1<<WGM12);
//	TCCR1B=(1<<CS11)|(1<<WGM12);// 1/8
//
//	OCR1A=0x40;

	// Init PWM on timer2
	TCCR2=(1<<WGM21)|(1<<WGM20)|(1<<CS20)|(1<<COM21); // Fast PWM

	DDRB = 0xFF;//0x08 | 0x04 | 0x02 | 0x01;

	resetSound();
}



uint8_t prevSample;

// Timer interrupt
//ISR(TIMER0_OVF_vect) {
//	OCR1A = prevSample;
//
//	PORTB |= 0x01;
//
//	prevSample = getNextSample();
//
//	PORTB &= ~0x01;
//}

uint8_t cnt;
// Timer interrupt
ISR(TIMER2_OVF_vect) {
//ISR(TIMER0_OVF_vect) {
#if MICROSOUND_FREQUENCY_DIVIDER > 1
	if ((cnt++) & (MICROSOUND_FREQUENCY_DIVIDER - 1)) {
//		int8_t next = soundBuffer[(bufferRead + 1) & BUFFER_MASK] - soundBuffer[bufferRead];
//		OCR1A = soundBuffer[bufferRead] + (int8_t)((next * ((cnt-1) & (MICROSOUND_FREQUENCY_DIVIDER - 1))) >> 4);
		return;
	}
#endif
	OCR1A = soundBuffer[bufferRead];
//	OCR1B = soundBuffer[bufferRead];
//	OCR2 = soundBuffer[bufferRead];
	bufferRead = (bufferRead + 1) & BUFFER_MASK;
}
