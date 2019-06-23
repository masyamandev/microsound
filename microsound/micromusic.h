#ifndef MICROMUSIC_INIT
#define MICROMUSIC_INIT

#include "microsound.h"


typedef void (*sampleSource)(soundChannel* channel, uint8_t data);


sampleSource samples[SAMPLES_SIZE];
sampleSource channelSamples[SAMPLES_SIZE];

const uint8_t *musicData;
uint16_t nextBeat;
uint8_t isMusicStopped;
//
//soundSource silenceSource(uint8_t data) {
//	return silence;
//}

inline void initMusic() {
	initSound();
	nextBeat = 0;
	isMusicStopped = 1;
//	uint8_t i;
//	for (i = 0; i < SAMPLES_SIZE; i++) {
//		samples[i] = silenceSource;
//	}
}

inline void setSample(uint8_t id, sampleSource sample) {
	samples[id] = sample;
}

#define COMMAND_PLAY		0b10000000
#define COMMAND_WAIT		0b01000000
#define COMMAND_VOLUME		0b00100000
#define COMMAND_INSTRUMENT	0b00010000
#define COMMAND_TEMPO		0b00000001
#define COMMAND_END			0b00000000

#define DATA_PLAY(channel, note, wait)			(COMMAND_PLAY | (wait << 4) | channel), (note)
#define DATA_WAIT(wait)							(COMMAND_WAIT | wait)
#define DATA_VOLUME(channel, vol)				(COMMAND_VOLUME | channel), (vol)
#define DATA_INSTRUMENT(channel, instrument)	(COMMAND_INSTRUMENT | channel), (instrument)
#define DATA_TEMPO(bpm)							(COMMAND_TEMPO), ((fromBpm(bpm) >> 8) & 0xFF), (fromBpm(bpm) & 0xFF)
#define DATA_END()								(COMMAND_END)

inline void fillMusicBuffer() {
	fillBuffer();
	if (isMusicStopped) {
		return;
	}
	while (beatCounter >= nextBeat) {
		uint8_t data = pgm_read_byte(musicData++);
		if (data & COMMAND_PLAY) {
			// 2 bytes [CWWWHHHH][NNNNNNNN]: C: command, HHHH: channelId, NNNNNNNN: note, WWW: wait
			uint8_t channel = data & 0b1111;
			uint8_t wait = (data >> 4) & 0b111;
			data = pgm_read_byte(musicData++);
			channelSamples[channel](channels[channel], data);
			nextBeat += wait;
		} else if (data & COMMAND_WAIT) {
			// 1 byte [CCWWWWWW]: CC: command, WWWWWW: wait
			nextBeat += data & 0b00111111;
		} else if (data & COMMAND_VOLUME) {
			// 2 bytes [CCC_HHHH][VVVVVVVV]: CCC: command, HHHH: channelId, VVVVVVVV: volume
			setVolume(data & 0b00001111, pgm_read_byte(musicData++));
		}  else if (data & COMMAND_INSTRUMENT) {
			// 2 bytes [CCCCHHHH][SSSSSSSS]: CCCC: command, HHHH: channelId, SSSSSSSS: sample
			channelSamples[data & 0b00001111] = samples[pgm_read_byte(musicData++)];
		} else if (data & COMMAND_TEMPO) {
			// 3 bytes [CCCCCCCC][TTTTTTTT][TTTTTTTT]: C: command, T: bpm increment counter
			uint16_t bpm = pgm_read_byte(musicData++) << 8;
			bpm += pgm_read_byte(musicData++);
			setBpm(bpm);
		} else {
			// COMMAND_END
			isMusicStopped = 1;
			break;
		}
	}
	fillBuffer();
}

inline void playMusic(const uint8_t *data) {
	resetSound();
	musicData = data;
	nextBeat = 0;
	isMusicStopped = 0;
}

#endif