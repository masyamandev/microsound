#include <inttypes.h>
#include <avr/io.h>
//#include <avr/iom8.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

#define SAMPLE_PIANO	0
#define SAMPLE_PIANO1	1
#define SAMPLE_PIANO2	2
#define SAMPLE_HARMONICA	3

//#define DECLICK
#define MICROSOUND_FREQUENCY_DIVIDER	1
#define VOICE_COUNTER	2
#define SAMPLE_COUNTER	16
#define INTERPOLATE_WAVE
#define INTERPOLATE_VOLUME

#include "microsound/devices/atmega8timer2cpu8mhz.h"
#include "microsound/micromusic.h"
#include "microsound/samples/instruments.h"
#include "microsound/samples/singlechannel.h"


const uint8_t test[] PROGMEM = {
		DATA_TEMPO(60),
		DATA_VOLUME(0, 128),
		DATA_PLAYSHORT(0, SAMPLE_PIANO, NOTE_A3, 2),
//		DATA_PLAYSHORT(0, SAMPLE_PIANO, NOTE_C5, 1),
//		DATA_PLAYSHORT(0, SAMPLE_PIANO, NOTE_A4, 1),
//		DATA_PLAYSHORT(0, SAMPLE_PIANO, NOTE_A4, 1),
		DATA_END()
};


int main(void)
{
	initMusic();
	setSample(SAMPLE_PIANO, pianoInit());
	setSample(SAMPLE_PIANO1, piano1Init());
	setSample(SAMPLE_PIANO2, piano2Init());
	setSample(SAMPLE_HARMONICA, harmonicaInit());

	sei();

	uint16_t prevBeatCounter = -1;
	while (1) {

		PORTB |= 0x01;
		fillMusicBuffer();
		PORTB &= ~0x01;

		if (isMusicStopped) {
			playMusic(test);
		}

	}
}
