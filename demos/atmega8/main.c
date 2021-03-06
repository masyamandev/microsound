/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

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
#define SAMPLE_MUSICBOX		5

#define NOISE_CALCULATION_WHEN_UNUSED // Use full calculation of noise channel on each sample to test performance
//#define BUFFER_BITS	16
//#define BUFFER_SIZE 128
//#define MICROSOUND_FREQUENCY_DIVIDER	4
//#define INTERPOLATION_STRENGTH	2
//#define INTERPOLATE_WAVE
#define CHANNELS_SIZE	5
#define SAMPLES_SIZE	16
#define USE_NOISE_CHANNEL

#include "../../microsound/devices/atmega8timer1.h"
#include "../../microsound/micromusic.h"

#include "../../microsound/instruments/piano.h"
#include "../../microsound/instruments/bassGuitar.h"
//#include "../../microsound/instruments/accordion.h"
#include "../../microsound/instruments/harmonica.h"
#include "../../microsound/instruments/overdrivenGuitarChord.h"
#include "../../microsound/instruments/percussion.h"
#include "../../microsound/instruments/musicbox.h"

#include "../../microsound/samples/oh_susanna.h"
#include "../../microsound/samples/for_elise.h"


int main(void)
{
	initMusic();
	setSample(SAMPLE_PERCUSSION, playPercussion);
	setSample(SAMPLE_PIANO, playPiano);
	setSample(SAMPLE_HARMONICA, playHarmonica);
	setSample(SAMPLE_BASS, playBassGuitar);
	setSample(SAMPLE_OVERDRIVE, playOverdrivenGuitarChord);
	setSample(SAMPLE_MUSICBOX, playMusicbox);

	sei();

	DDRB |= 0x01;
	while (1) {

		PORTB |= 0x01;
		fillMusicBuffer();
		PORTB &= ~0x01;

		// Simulate other CPU usage
		while (samplesInBuffer > 4) {};

		if (isMusicStopped) {
			playMusic(ohSusannaSong);
		}

	}
}
