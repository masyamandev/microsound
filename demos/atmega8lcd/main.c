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

//#define BUFFER_BITS	16
#define BUFFER_SIZE 64
//#define MICROSOUND_FREQUENCY_DIVIDER	4
//#define INTERPOLATION_STRENGTH	2
//#define INTERPOLATE_WAVE
#define CHANNELS_SIZE	5
#define SAMPLES_SIZE	16
#define USE_NOISE_CHANNEL

void fillBufferAtLeastMs(uint8_t delay);
//#define _delay_ms	fillBufferAtLeastMs


#include "../../microsound/devices/atmega8timer2cpu8mhz.h"
#include "../../microsound/micromusic.h"

//#include "../../microsound/instruments/piano.h"
//#include "../../microsound/instruments/bassGuitar.h"
////#include "../../microsound/instruments/accordion.h"
//#include "../../microsound/instruments/harmonica.h"
//#include "../../microsound/instruments/overdrivenGuitarChord.h"
//#include "../../microsound/instruments/percussion.h"
#include "../../microsound/instruments/musicbox.h"


//#include "../../microsound/samples/singlechannel.h"
//#include "../../microsound/samples/oh_susanna.h"
#include "../../microsound/samples/for_elise.h"

#include "../../lcd1602/lcd1602.h"

const uint8_t PIANO_CHAR_A[] PROGMEM = {
		0b10101,
		0b10101,
		0b10101,
		0b10101,
		0b10001,
		0b11011,
		0b11011,
		0b11011
};
const uint8_t PIANO_CHAR_B[] PROGMEM = {
		0b10101,
		0b10101,
		0b10101,
		0b10101,
		0b00101,
		0b01101,
		0b01101,
		0b01101
};
const uint8_t PIANO_CHAR_C[] PROGMEM = {
		0b10101,
		0b10101,
		0b10101,
		0b10101,
		0b00100,
		0b01110,
		0b01110,
		0b01110
};


void fillBufferAtLeastMs(uint8_t delay) {
	fillMusicBuffer();
}

#define CUSTOM_CHARS	4 // For some reason it's buggy on my LCD when value 5 is set

int main(void)
{
	initLCD();

	initCharProgmem(5, PIANO_CHAR_A);
	initCharProgmem(6, PIANO_CHAR_B);
	initCharProgmem(7, PIANO_CHAR_C);
	cursor(1, 0);
	uint8_t i;
	for(i = 0; i < 5; i++) {
		printChar(5);
		printChar(6);
		printChar(7);
		printChar(5);
	}

	initMusic();
//	setSample(SAMPLE_PERCUSSION, playPercussion);
//	setSample(SAMPLE_PIANO, playPiano);
//	setSample(SAMPLE_HARMONICA, playHarmonica);
//	setSample(SAMPLE_BASS, playBassGuitar);
//	setSample(SAMPLE_OVERDRIVE, playOverdrivenGuitarChord);
	setSample(SAMPLE_MUSICBOX, playMusicbox);

	sei();

	while (1) {

		fillBufferAtLeastMs(0);

		cursor(0, 0);

		uint8_t pos;
		uint8_t currentChar = 0;
		static uint8_t customCharsPos[CUSTOM_CHARS];

		for (pos = 0; pos < 16; pos++) {
			uint8_t note1 = 0;
			uint8_t note2 = 0;
			uint8_t note3 = 0;
			for (i = 0; i < CHANNELS_SIZE; i++) {
				if (channels[i]->waveStep == pgm_read_word(&frequencies[NOTE_C2 + pos * 3])) {
					note1 += channels[i]->currentVolume;
				}
				if (channels[i]->waveStep == pgm_read_word(&frequencies[NOTE_C2 + pos * 3 + 1])) {
					note2 += channels[i]->currentVolume;
				}
				if (channels[i]->waveStep == pgm_read_word(&frequencies[NOTE_C2 + pos * 3 + 2])) {
					note3 += channels[i]->currentVolume;
				}
			}

			if (note1 + note2 + note3 > 0) {
			    uint8_t customChar[8];
				uint8_t k;
				for (k = 0; k < 8; k++) {
					customChar[7 - k] = ((note1 > (k << 3)) ? 0b10000 : 0) |
							((note2 > (k << 3)) ? 0b00100 : 0) |
							((note3 > (k << 3)) ? 0b00001 : 0);
				}
				fillBufferAtLeastMs(0);

				if (customCharsPos[currentChar] != pos && customCharsPos[currentChar] < 16) {
					cursor(0, customCharsPos[currentChar]);
					printChar(' ');
					customCharsPos[currentChar] = pos;
				}
				cursor(0, pos);

				printChar(currentChar);
				initChar(currentChar, customChar);
				currentChar++;
				if (currentChar >= CUSTOM_CHARS) {
					currentChar = 0;
				}
			} else {
				printChar(' ');
			}

			fillBufferAtLeastMs(0);
		}


		if (isMusicStopped) {
			playMusic(forElise);
		}

	}
}
