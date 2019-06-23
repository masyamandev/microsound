#include <inttypes.h>
#include <avr/io.h>
//#include <avr/iom8.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

#define SAMPLE_SILENCE	0
#define SAMPLE_PIANO	1
#define SAMPLE_PIANO1	2
#define SAMPLE_PIANO2	3
#define SAMPLE_HARMONICA	4
#define SAMPLE_PERCUSSION	5

//#define DECLICK
#define MICROSOUND_FREQUENCY_DIVIDER	1
//#define GLOBAL_INTERPOLATION_LINEAR
//#define INTERPOLATION_STRENGTH	2
#define CHANNELS_SIZE	8
//#define SAMPLE_COUNTER	16
//#define INTERPOLATE_WAVE
#define INTERPOLATE_VOLUME

#include "microsound/devices/atmega8timer2cpu8mhz.h"
//#include "microsound/micromusic.h"
//#include "microsound/samples/instruments.h"
//#include "microsound/samples/singlechannel.h"

#include "microsound/instruments/common/sin.h"
#include "microsound/instruments/common/expneg.h"


//const uint8_t test[] PROGMEM = {
//		DATA_TEMPO(60),
//		DATA_VOLUME(0, 128),
//		DATA_VOLUME(1, 128),
//		DATA_VOLUME(2, 128),
//		DATA_VOLUME(3, 32),
//		DATA_PLAYSHORT(0, SAMPLE_PIANO, NOTE_A3, 1),
////		DATA_PLAYSHORT(3, SAMPLE_HARMONICA, NOTE_C4, 0),
////		DATA_PLAYSHORT(2, SAMPLE_PIANO2, NOTE_C4, 0),
////		DATA_PLAYSHORT(1, SAMPLE_PIANO1, NOTE_E4, 0),
//		DATA_PLAYSHORT(0, SAMPLE_PIANO, NOTE_G4, 1),
////		DATA_PLAYSHORT(0, SAMPLE_PERCUSSION, NOTE_G4, 1),
//		DATA_END()
//};


int main(void)
{
//	interpolationValue = 0;
//	interpolationDiff = 0;
//	interpolationDiffDiff = 0;

//	initMusic();
//	setSample(SAMPLE_PIANO, pianoInit());
//	setSample(SAMPLE_PIANO1, piano1Init());
//	setSample(SAMPLE_PIANO2, piano2Init());
//	setSample(SAMPLE_HARMONICA, harmonicaInit());
//	setSample(SAMPLE_PERCUSSION, percussionInit());

	initSound();

	setBpm(fromBpm(60));

//	uint8_t i;
//	for (i = 0; i < CHANNELS_SIZE; i++) {
//		channels[i].waveForm = sinTable;
//		channels[i].waveFormMask = SAMPLE_MASK;
//	}

//	channel1ChannelData.waveStep = frequencies[NOTE_A3];
//	channel1ChannelData.waveForm = sinTable;
////	channel1ChannelData.waveFormMask = SAMPLE_MASK;
//	channel1ChannelData.currentVolume = 128;
//
//	channel1ChannelData.volumeForm = expNegTable;
//	channel1ChannelData.volumeFormLength = 255;

	sei();

	channel0ChannelData.currentVolume = 128;

	uint16_t beat = 99;

	while (1) {

		if (beatCounter != beat) {
			beat = beatCounter;

			channel0ChannelData.waveStep = frequencies[NOTE_A3];
			channel0ChannelData.waveForm = sinTable;
		//	channel0ChannelData.waveFormMask = SAMPLE_MASK;
			channel0ChannelData.instrumentVolume = 128;

			channel0ChannelData.volumeForm = expNegTable;
			channel0ChannelData.volumeFormLength = 255;
			channel0ChannelData.volumeSample = 0;
			channel0ChannelData.volumeTicksPerSample = 2;

		}

		PORTB |= 0x01;
		//fillMusicBuffer();
		fillBuffer();
		PORTB &= ~0x01;

//		if (isMusicStopped) {
//			playMusic(test);
//		}

	}
}
