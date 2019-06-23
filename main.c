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
#define INTERPOLATE_WAVE
#define INTERPOLATE_VOLUME

#include "microsound/devices/atmega8timer2cpu8mhz.h"
//#include "microsound/micromusic.h"
//#include "microsound/samples/instruments.h"
//#include "microsound/samples/singlechannel.h"

#include "microsound/instruments/common/math.h"


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

	setBpm(fromBpm(440));

//	uint8_t i;
//	for (i = 0; i < CHANNELS_SIZE; i++) {
//		channels[i].waveForm = sinTable;
//		channels[i].waveFormMask = SAMPLE_MASK;
//	}

	channel1ChannelData.step = frequencies[NOTE_A3];
	channel1ChannelData.waveForm = sinTable;
//	channel1ChannelData.waveFormMask = SAMPLE_MASK;
	channel1ChannelData.currentVolume = 128;


	sei();



	while (1) {
//		while (bufferWrite != bufferRead) {
//
//				if ((sampleCounter--) == 0) {
//					sampleCounter = bpmIncrementAt;
//					beatCounter++;
//				}
//				downsampleCounter = (downsampleCounter + 1) & VOLUME_CHANGE_DOWNSAMPLING_MASK;
//
//
//			channel.sample -= channel.step * 3;
//				uint16_t val = 0x8000;
//				int i;
//				for (i = CHANNELS_SIZE - 1; i >= 0; i--) {
//
//					// Get wave
//									uint16_t sample = channel.sample;
//									uint8_t sampleId = ((uint8_t)(sample >> 8)) & 31;//channel.waveFormMask;
//									int8_t tone = channel.waveForm[sampleId];
//									#ifdef INTERPOLATE_WAVE
//										uint8_t subsampleTone = sample;
//										tone += (( channel.waveForm[sampleId + 1] - tone) * subsampleTone) >> 8;
//									#endif
//									channel.sample += channel.step;
//
//									val +=
//										#ifdef DECLICK
//											channel.prevValue =
//										#endif
//											tone * channel.currentVolume;
//
////					// Get wave
////					uint16_t sample = channels[i].sample;
////					uint8_t sampleId = ((uint8_t)(sample >> 8)) & 31;//channels[i].waveFormMask;
////					int8_t tone = channels[i].waveForm[sampleId];
////					#ifdef INTERPOLATE_WAVE
////						uint8_t subsampleTone = sample;
////						tone += (( channels[i].waveForm[sampleId + 1] - tone) * subsampleTone) >> 8;
////					#endif
////					channels[i].sample += channels[i].step;
////
////					val +=
////						#ifdef DECLICK
////							channels[i].prevValue =
////						#endif
////							tone * channels[i].currentVolume;
//				}
//
//				#ifdef DECLICK
//					declickValue -= (int8_t) declickValue >> 8;
//					val += declickValue;
//				#endif
//
//				soundBuffer[bufferWrite] = val >> 8;
//
//
//		//		soundBuffer[bufferWrite] = getNextInterpolatedSample();
//		//		soundBuffer[bufferWrite] = getNextSample();
//				bufferWrite = (bufferWrite + 1) & BUFFER_MASK;
//			}

//		while (bufferWrite != bufferRead) {
//
////				if ((sampleCounter--) == 0) {
////					sampleCounter = bpmIncrementAt;
////					beatCounter++;
////				}
////
////				downsampleCounter = (downsampleCounter + 1) & VOLUME_CHANGE_DOWNSAMPLING_MASK;
//
//				uint16_t val = 0x8000;
//				val += channel1NextSample();
//				val += channel2NextSample();
//				val += channel3NextSample();
//				val += channel4NextSample();
//			//	val += channel5NextSample();
//			//	val += channel6NextSample();
//			//	val += channel7NextSample();
//			//	val += channel8NextSample();
//				soundBuffer[bufferWrite] = val >> 8;
//
////			soundBuffer[bufferWrite] = getNextInterpolatedSample();
//	//		soundBuffer[bufferWrite] = getNextSample();
//			bufferWrite = (bufferWrite + 1) & BUFFER_MASK;
//		}

		PORTB |= 0x01;
		//fillMusicBuffer();
		fillBuffer();
		PORTB &= ~0x01;

//		if (isMusicStopped) {
//			playMusic(test);
//		}

	}
}
