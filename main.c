#include <inttypes.h>
#include <avr/io.h>
//#include <avr/iom8.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

#define SAMPLE_PERCUSSION	0
#define SAMPLE_PIANO		1
#define SAMPLE_HARMONICA	2
#define SAMPLE_BASS			3
#define SAMPLE_OVERDRIVE	4

//#define MICROSOUND_FREQUENCY_DIVIDER	4
//#define INTERPOLATION_STRENGTH	2
#define CHANNELS_SIZE	5
#define SAMPLES_SIZE	16
#define USE_NOISE_CHANNEL

#include "microsound/devices/atmega8timer2cpu8mhz.h"
#include "microsound/micromusic.h"

#include "microsound/instruments/piano.h"
#include "microsound/instruments/bassGuitar.h"
//#include "microsound/instruments/accordion.h"
#include "microsound/instruments/harmonica.h"
#include "microsound/instruments/overdrivenGuitarChord.h"
#include "microsound/instruments/percussion.h"


#ifndef OVERDRIVE_SHORT
#define OVERDRIVE_SHORT 0
#endif

//#include "microsound/samples/singlechannel.h"
//#include "microsound/samples/twochannels.h"
#include "microsound/samples/oh_susanna.h"



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
//		DATA_PLAY(0, NOTE_E4, 1),
//		DATA_PLAY(0, NOTE_E3, 1),


		DATA_INSTRUMENT(0, SAMPLE_OVERDRIVE),
		DATA_INSTRUMENT(3, SAMPLE_OVERDRIVE),
//		DATA_PLAY(0, NOTE_G2, 0),
		DATA_PLAY(0, NOTE_C2, 1),
//		DATA_PLAY(3, NOTE_C4, 0),
//		DATA_PLAY(2, NOTE_C3, 0),
//		DATA_PLAY(1, NOTE_E3, 0),
//		DATA_PLAY(0, NOTE_G3, 0),
		DATA_PLAY(0, NOTE_C3, 1),

		DATA_TEMPO(220),
		DATA_INSTRUMENT(0, SAMPLE_OVERDRIVE),
		DATA_PLAY(0, NOTE_C3 | OVERDRIVE_SHORT, 1),
		DATA_PLAY(0, NOTE_D3 | OVERDRIVE_SHORT, 1),
		DATA_PLAY(0, NOTE_E3 | OVERDRIVE_SHORT, 1),
		DATA_PLAY(0, NOTE_F3, 4),
		DATA_END()
};

const uint8_t testPercussion[] PROGMEM = {
		DATA_TEMPO(480),
		DATA_INSTRUMENT(0, SAMPLE_PERCUSSION),
		DATA_VOLUME(0, 128),

//		DATA_PLAY(0, PERCUSSION_HAT_L, 1),
//		DATA_PLAY(0, PERCUSSION_HAT_H, 1),
//		DATA_PLAY(0, PERCUSSION_BAR_L, 1),
//		DATA_PLAY(0, PERCUSSION_BAR_H, 1),

		DATA_PLAY(0, PERCUSSION_HAT_H, 1),
		DATA_PLAY(0, PERCUSSION_HAT_L, 1),
		DATA_PLAY(0, PERCUSSION_BAR_H, 1),
		DATA_PLAY(0, PERCUSSION_BAR_L, 1),
		DATA_PLAY(0, PERCUSSION_HAT_H, 2),
		DATA_PLAY(0, PERCUSSION_HAT_L, 2),
		DATA_PLAY(0, PERCUSSION_BAR_H, 2),
		DATA_PLAY(0, PERCUSSION_BAR_L, 2),
		DATA_PLAY(0, PERCUSSION_HAT_H, 2),
		DATA_END()
};

int main(void)
{
	initMusic();
	setSample(SAMPLE_PERCUSSION, playPercussion);
	setSample(SAMPLE_PIANO, playPiano);
	setSample(SAMPLE_HARMONICA, playHarmonica);
	setSample(SAMPLE_BASS, playBassGuitar);
	setSample(SAMPLE_OVERDRIVE, playOverdrivenGuitarChord);

	sei();

	while (1) {

		PORTB |= 0x01;
		fillMusicBuffer();
		PORTB &= ~0x01;

		if (isMusicStopped) {
			playMusic(ohSusannaSong);
		}

	}
}
