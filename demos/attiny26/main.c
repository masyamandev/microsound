#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

//#define SAMPLE_LENGTH 	64

#define SAMPLE_MUSICBOX		0

#define INLINE_BUFFER_FILL inline
#define INLINE_SOUND_CONTROL inline
#define INLINE_MULTIPLICATION_SIGNED_UNSIGNED // do not inline
#define INLINE_WAVETABLE_SOUND_GENERATOR // do not inline
#define SPEED_OPTIMIZED_MULTIPLICATION
#define SIMPLIFIED_MULTIPLICATION

#define MICROSOUND_STATIC_VOLUME	2 // Use simplified sound control with common volume for all channels
//#define BUFFER_BITS	16
//#define BUFFER_SIZE 64
#define MICROSOUND_FREQUENCY_DIVIDER	2
//#define INTERPOLATION_STRENGTH	2
//#define INTERPOLATE_WAVE
#define CHANNELS_SIZE	4
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
		DATA_INSTRUMENT(3, SAMPLE_MUSICBOX),
//		DATA_VOLUME(0, 80),
//		DATA_VOLUME(1, 80),
//		DATA_VOLUME(2, 80),
//		DATA_VOLUME(3, 80),

		DATA_PLAY(0, NOTE_E5, 2),
		DATA_PLAY(1, NOTE_Eb5, 2),
		// 10
		DATA_PLAY(0, NOTE_E5, 2),
		DATA_PLAY(1, NOTE_Eb5, 2),
		DATA_PLAY(0, NOTE_E5, 2),
		DATA_PLAY(2, NOTE_B4, 2),
		DATA_PLAY(3, NOTE_D5, 2),
		DATA_PLAY(0, NOTE_C5, 2),
		// 11
		DATA_PLAY(1, NOTE_A4, 0),
		DATA_PLAY(2, NOTE_A2, 2),
		DATA_PLAY(3, NOTE_E3, 2),
		DATA_PLAY(0, NOTE_A3, 2),
		DATA_PLAY(1, NOTE_C4, 2),
		DATA_PLAY(2, NOTE_E4, 2),
		DATA_PLAY(3, NOTE_A4, 2),
		// 12
		DATA_PLAY(0, NOTE_B4, 0),
		DATA_PLAY(1, NOTE_E2, 2),
		DATA_PLAY(2, NOTE_E3, 2),
		DATA_PLAY(3, NOTE_Ab3, 2),
		DATA_PLAY(0, NOTE_E4, 2),
		DATA_PLAY(1, NOTE_Ab4, 2),
		DATA_PLAY(2, NOTE_B4, 2),
		// 13
		DATA_PLAY(3, NOTE_C5, 0),
		DATA_PLAY(0, NOTE_A2, 2),
		DATA_PLAY(1, NOTE_E3, 2),
		DATA_PLAY(2, NOTE_A3, 2),
		DATA_PLAY(3, NOTE_E4, 2),
		DATA_PLAY(0, NOTE_E5, 2),
		DATA_PLAY(1, NOTE_Eb5, 2),
		// 14
		DATA_PLAY(0, NOTE_E5, 2),
		DATA_PLAY(1, NOTE_Eb5, 2),
		DATA_PLAY(0, NOTE_E5, 2),
		DATA_PLAY(2, NOTE_B4, 2),
		DATA_PLAY(3, NOTE_D5, 2),
		DATA_PLAY(0, NOTE_C5, 2),
		// 15
		DATA_PLAY(1, NOTE_A4, 0),
		DATA_PLAY(2, NOTE_A2, 2),
		DATA_PLAY(3, NOTE_E3, 2),
		DATA_PLAY(0, NOTE_A3, 2),
		DATA_PLAY(1, NOTE_C4, 2),
		DATA_PLAY(2, NOTE_E4, 2),
		DATA_PLAY(3, NOTE_A4, 2),
		// 16
		DATA_PLAY(0, NOTE_B4, 0),
		DATA_PLAY(1, NOTE_E2, 2),
		DATA_PLAY(2, NOTE_E3, 2),
		DATA_PLAY(3, NOTE_Ab3, 2),
		DATA_PLAY(0, NOTE_E4, 2),
		DATA_PLAY(1, NOTE_C5, 2),
		DATA_PLAY(2, NOTE_B4, 2),
		// 17
		DATA_PLAY(3, NOTE_A4, 0),
		DATA_PLAY(0, NOTE_A2, 2),
		DATA_PLAY(1, NOTE_E3, 2),
		DATA_PLAY(2, NOTE_A3, 2),
		DATA_PLAY(3, NOTE_B4, 2),
		DATA_PLAY(0, NOTE_C5, 2),
		DATA_PLAY(1, NOTE_D5, 2),
		// 18
		DATA_PLAY(2, NOTE_E5, 0),
		DATA_PLAY(3, NOTE_C3, 2),
		DATA_PLAY(0, NOTE_G3, 2),
		DATA_PLAY(1, NOTE_C4, 2),
		DATA_PLAY(2, NOTE_G4, 2),
		DATA_PLAY(3, NOTE_F5, 2),
		DATA_PLAY(0, NOTE_E5, 2),
		// 19
		DATA_PLAY(1, NOTE_D5, 0),
		DATA_PLAY(2, NOTE_G2, 2),
		DATA_PLAY(3, NOTE_G3, 2),
		DATA_PLAY(0, NOTE_A3, 2),
		DATA_PLAY(1, NOTE_F4, 2),
		DATA_PLAY(2, NOTE_E5, 2),
		DATA_PLAY(3, NOTE_D5, 2),
		// 20
		DATA_PLAY(0, NOTE_C5, 0),
		DATA_PLAY(1, NOTE_A2, 2),
		DATA_PLAY(2, NOTE_E3, 2),
		DATA_PLAY(3, NOTE_A3, 2),
		DATA_PLAY(0, NOTE_E4, 2),
		DATA_PLAY(1, NOTE_D5, 2),
		DATA_PLAY(2, NOTE_C5, 2),
		// 21
		DATA_PLAY(3, NOTE_B4, 0),
		DATA_PLAY(0, NOTE_E2, 2),
		DATA_PLAY(1, NOTE_E3, 2),
		DATA_PLAY(2, NOTE_E4, 2),
		DATA_PLAY(2, NOTE_E4, 2),
		DATA_PLAY(3, NOTE_E5, 2),
		DATA_PLAY(2, NOTE_E4, 2),

//		DATA_WAIT(16),

		DATA_END()
};

int main(void)
{
	initMusic();
	setSample(SAMPLE_MUSICBOX, playMusicbox);

	sei();

//	DDRB |= 0x10;
	while (1) {

//		PORTB |= 0x10;
		fillMusicBuffer();
//		PORTB &= ~0x10;

		// Simulate other CPU usage
//		while (samplesInBuffer > 4) {};

		if (isMusicStopped) {
			playMusic(test);
		}


	}
}
