#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#define SAMPLE_PIANO		0
#define SAMPLE_HARMONICA	0
#define SAMPLE_BASS			0
#define SAMPLE_MUSICBOX		0

#define MICROSOUND_STATIC_VOLUME	2
//#define BUFFER_BITS	16
//#define BUFFER_SIZE 64
#define MICROSOUND_FREQUENCY_DIVIDER	4
//#define INTERPOLATION_STRENGTH	2
//#define INTERPOLATE_WAVE
#define CHANNELS_SIZE	3
#define SAMPLES_SIZE	1
//#define USE_NOISE_CHANNEL

#include "../../microsound/devices/attiny26timers01cpu16mhz.h"
#include "../../microsound/micromusic.h"

#include "../../microsound/instruments/musicbox.h"

const uint8_t test[] PROGMEM = {
		DATA_TEMPO(480),
		DATA_INSTRUMENT(0, SAMPLE_MUSICBOX),
		DATA_INSTRUMENT(1, SAMPLE_MUSICBOX),
		DATA_INSTRUMENT(2, SAMPLE_MUSICBOX),
//		DATA_INSTRUMENT(3, SAMPLE_MUSICBOX),
//		DATA_VOLUME(0, 80),
//		DATA_VOLUME(1, 80),
//		DATA_VOLUME(2, 80),
//		DATA_VOLUME(3, 80),

		// 1
		DATA_PLAY(0, NOTE_E5, 2),
		DATA_PLAY(1, NOTE_Eb5, 2),
		// 2
		DATA_PLAY(2, NOTE_E5, 2),
		DATA_PLAY(0, NOTE_Eb5, 2),
		DATA_PLAY(1, NOTE_E5, 2),
		DATA_PLAY(2, NOTE_B4, 2),
		DATA_PLAY(0, NOTE_D5, 2),
		DATA_PLAY(1, NOTE_C5, 2),
		// 3
		DATA_PLAY(2, NOTE_A4, 0),
		DATA_PLAY(0, NOTE_A2, 2),
		DATA_PLAY(1, NOTE_E3, 2),
		DATA_PLAY(2, NOTE_A3, 2),
		DATA_PLAY(0, NOTE_C4, 2),
		DATA_PLAY(1, NOTE_E4, 2),
		DATA_PLAY(2, NOTE_A4, 2),
		// 4
		DATA_PLAY(0, NOTE_B4, 0),
		DATA_PLAY(1, NOTE_E2, 2),
		DATA_PLAY(2, NOTE_E3, 2),
		DATA_PLAY(0, NOTE_Ab3, 2),
		DATA_PLAY(1, NOTE_E4, 2),
		DATA_PLAY(2, NOTE_Ab4, 2),
		DATA_PLAY(0, NOTE_B4, 2),
		// 5
		DATA_PLAY(1, NOTE_C5, 0),
		DATA_PLAY(2, NOTE_A2, 2),
		DATA_PLAY(0, NOTE_E3, 2),
		DATA_PLAY(1, NOTE_A3, 2),
		DATA_PLAY(2, NOTE_E4, 2),
		DATA_PLAY(0, NOTE_E5, 2),
		DATA_PLAY(1, NOTE_Eb5, 2),
		// 6
		DATA_PLAY(2, NOTE_E5, 2),
		DATA_PLAY(0, NOTE_Eb5, 2),
		DATA_PLAY(1, NOTE_E5, 2),
		DATA_PLAY(2, NOTE_B4, 2),
		DATA_PLAY(0, NOTE_D5, 2),
		DATA_PLAY(1, NOTE_C5, 2),
		// 7
		DATA_PLAY(2, NOTE_A4, 0),
		DATA_PLAY(0, NOTE_A2, 2),
		DATA_PLAY(1, NOTE_E3, 2),
		DATA_PLAY(2, NOTE_A3, 2),
		DATA_PLAY(0, NOTE_C4, 2),
		DATA_PLAY(1, NOTE_E4, 2),
		DATA_PLAY(2, NOTE_A4, 2),
		// 8
		DATA_PLAY(0, NOTE_B4, 0),
		DATA_PLAY(1, NOTE_E2, 2),
		DATA_PLAY(2, NOTE_E3, 2),
		DATA_PLAY(0, NOTE_Ab3, 2),
		DATA_PLAY(1, NOTE_E4, 2),
		DATA_PLAY(2, NOTE_C5, 2),
		DATA_PLAY(0, NOTE_B4, 2),
		// 9
		DATA_PLAY(1, NOTE_A4, 0),
		DATA_PLAY(2, NOTE_A2, 2),
		DATA_PLAY(0, NOTE_E3, 2),
		DATA_PLAY(1, NOTE_A3, 4),

//		DATA_WAIT(16),

		DATA_END()
};

int main(void)
{
	initMusic();
	setSample(SAMPLE_MUSICBOX, playMusicbox);

	sei();

	while (1) {

		PORTB |= 0x10;
		fillMusicBuffer();
		PORTB &= ~0x10;

		// Simulate other CPU usage
		while (samplesInBuffer > 4) {};

		if (isMusicStopped) {
			playMusic(test);
		}


	}
}
