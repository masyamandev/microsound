
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
	OCR1B = 127;
	OCR1C = 0xFF;

	// Init timer 0 interrupts
	TCCR0A = (1<<CS01);
	TCCR0B = (1<<WGM01);
	OCR0A = (F_CPU / 8 / MICROSOUND_FREQUENCY);

//	TIMSK = (1<<TOIE0);
	TIMSK = (1<<OCIE0A);

	// Set PB1 as output (pin2)
	DDRB = 0xFF;//0x02;

	resetSound();
}


// Timer0 interrupt
ISR(TIMER0_COMPA_vect) {
	OCR1B = sampleToUint8(getNextInterpolatedSample());
}
