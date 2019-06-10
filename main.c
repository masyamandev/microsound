#include <avr/io.h>
#include <avr/interrupt.h>

#define VOICE_COUNTER	2
#define INTERPOLATE_WAVE
#define INTERPOLATE_VOLUME

#include "microsound/devices/atmega8timer2cpu8mhz.h"
#include "microsound/samples/instruments.h"

int main(void)
{

	initSound();
	pianoInit();
	piano1Init();
	harmonicaInit();

	bpmIncrementAt = fromBpm(60);

	sei();

	uint16_t prevBeatCounter = -1;
	while (1) {

		PORTB |= 0x01;
		fillBuffer();
		PORTB &= ~0x01;

		if (prevBeatCounter != beatCounter) {
			if (beatCounter & 1) {
				playSound(0, piano(FREQ_A3), 255);
//				playSound(1, harmonicaPlayNote(FREQ_A3));
//				harmonicaPlayNote(FREQ_A3);
//				playSound(1, silence());
			} else {
				playSound(0, piano(FREQ_A4), 255);
//				playSound(0, harmonica(FREQ_A3), 255);
//				harmonicaPlayNote(FREQ_A4);
//				playSound(0, silence());
			}

//			if (beatCounter >= FREQ_ARRAY_SIZE) {
//				beatCounter = 0;
//			}
//			playSound(0, piano(frequencies[beatCounter]), 255);

			prevBeatCounter = beatCounter;
		}

	}
}
