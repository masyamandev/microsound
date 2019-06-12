#include <inttypes.h>
#include <avr/io.h>
//#include <avr/iom8.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

//#define DECLICK
#define MICROSOUND_FREQUENCY_DIVIDER	1
#define VOICE_COUNTER	2
#define INTERPOLATE_WAVE
#define INTERPOLATE_VOLUME

#include "microsound/devices/atmega8timer2cpu8mhz.h"
#include "microsound/samples/instruments.h"

int main(void)
{

	initSound();
	sampleSource piano = pianoInit();
	sampleSource piano1 = piano1Init();
	sampleSource piano2 = piano2Init();
	sampleSource harmonica = harmonicaInit();

	bpmIncrementAt = fromBpm(60);
//	bpmIncrementAt = fromBpm(880);

	sei();

	uint16_t prevBeatCounter = -1;
	while (1) {

		PORTB |= 0x01;
		fillBuffer();
		PORTB &= ~0x01;

		if (prevBeatCounter != beatCounter) {
			if (beatCounter & 1) {
				playSound(0, piano(NOTE_A3), 255);
//				playSound(0, harmonica(NOTE_A3), 255);
//				harmonicaPlayNote(NOTE_A3);
//				playSound(1, silence());
			} else {
				playSound(0, piano(NOTE_A4), 255);
//				playSound(0, harmonica(NOTE_A4), 255);
//				harmonicaPlayNote(NOTE_A4);
//				playSound(0, silence());
			}

//			switch (beatCounter & 7) {
////			case 0:
////				playSound(0, piano(NOTE_C3), 255);
////				break;
////			case 1:
////				playSound(1, piano1(NOTE_E3), 255);
////				break;
////			case 2:
////				playSound(2, piano2(NOTE_G3), 255);
////				break;
//			case 3:
////				playSound(3, piano(NOTE_C4), 96);
//				playSound(0, piano(NOTE_C3), 128);
//				playSound(1, piano1(NOTE_E3), 128);
//				playSound(2, piano2(NOTE_G3), 128);
//				break;
//			}

//			if (beatCounter >= NOTE_ARRAY_SIZE) {
//				beatCounter = 0;
//			}
//			playSound(0, piano(frequencies[beatCounter]), 255);

			prevBeatCounter = beatCounter;
		}

	}
}
