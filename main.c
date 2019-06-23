#include <inttypes.h>
#include <avr/io.h>
//#include <avr/iom8.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

//#define SAMPLE_SILENCE	0
#define SAMPLE_PIANO		1
#define SAMPLE_ACCORDION	2
//#define SAMPLE_PIANO2	3
//#define SAMPLE_HARMONICA	4
//#define SAMPLE_PERCUSSION	5

#define MICROSOUND_FREQUENCY_DIVIDER	1
//#define GLOBAL_INTERPOLATION_LINEAR
//#define INTERPOLATION_STRENGTH	2
#define CHANNELS_SIZE	5
#define SAMPLES_SIZE	16

#include "microsound/devices/atmega8timer2cpu8mhz.h"
#include "microsound/micromusic.h"

#include "microsound/instruments/piano.h"
#include "microsound/instruments/accordion.h"

#include "microsound/samples/singlechannel.h"
#include "microsound/samples/twochannels.h"


const uint8_t test[] PROGMEM = {
		DATA_TEMPO(60),
		DATA_INSTRUMENT(0, SAMPLE_PIANO),
		DATA_INSTRUMENT(1, SAMPLE_PIANO),
		DATA_INSTRUMENT(2, SAMPLE_PIANO),
		DATA_INSTRUMENT(3, SAMPLE_PIANO),
		DATA_VOLUME(0, 80),
		DATA_VOLUME(1, 80),
		DATA_VOLUME(2, 80),
		DATA_VOLUME(3, 128),
		DATA_PLAY(3, NOTE_C2, 1),
//		DATA_PLAY(3, NOTE_C4, 0),
		DATA_PLAY(2, NOTE_C3, 0),
		DATA_PLAY(1, NOTE_E3, 0),
		DATA_PLAY(0, NOTE_G3, 1),
		DATA_TEMPO(440),
		DATA_INSTRUMENT(3, SAMPLE_ACCORDION),
		DATA_PLAY(3, NOTE_C4, 1),
		DATA_PLAY(3, NOTE_D4, 1),
		DATA_PLAY(3, NOTE_E4, 1),
		DATA_PLAY(3, NOTE_F4, 4),
		DATA_END()
};


int main(void)
{
	initMusic();
	setSample(SAMPLE_PIANO, playPiano);
	setSample(SAMPLE_ACCORDION, playAccordion);

	sei();

	while (1) {

		PORTB |= 0x01;
		fillMusicBuffer();
		PORTB &= ~0x01;

		if (isMusicStopped) {
			playMusic(test);
		}

	}
}
