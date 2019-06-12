#ifndef MICROMUSIC_INIT
#define MICROMUSIC_INIT

#include "microsound.h"

sampleSource samples[SAMPLE_COUNTER];

const uint8_t *musicData;
uint16_t nextBeat;
uint8_t isMusicStopped;

inline void initMusic() {
	initSound();
	nextBeat = 0;
	isMusicStopped = 1;
}

inline void setSample(uint8_t id, sampleSource sample) {
	samples[id] = sample;
}

#define COMMAND_PLAYSHORT	0b10000000
#define COMMAND_WAIT		0b01000000
#define COMMAND_VOLUME		0b00100000
#define COMMAND_TEMPO		0b00000001
#define COMMAND_END			0b00000000

#define DATA_PLAYSHORT(channel, sample, note, wait)		(COMMAND_PLAYSHORT | (sample << 3) | channel), ((note << 3) | wait)
#define DATA_WAIT(wait)				(COMMAND_WAIT | wait)
#define DATA_VOLUME(channel, vol)	(COMMAND_VOLUME | channel), (vol)
#define DATA_TEMPO(bpm)				(COMMAND_TEMPO), (fromBpm(bpm) >> 8), (fromBpm(bpm) & 0xFF)

inline void fillMusicBuffer() {
	fillBuffer();
	if (isMusicStopped) {
		return;
	}
	while (beatCounter >= nextBeat) {
		uint8_t data = pgm_read_byte(musicData++);
		if (data & COMMAND_PLAYSHORT) {
			// 2 bytes [CSSSSHHH][NNNNNWWW]: C: command, SSSS: sampleId,  HHH: channelId, NNNNN: note, WWW: wait
			uint8_t channel = data & 0b111;
			uint8_t sample = (data >> 3) & 0b1111;
			data = pgm_read_byte(musicData++);
			playSound(channel, samples[sample](data >> 3));
			nextBeat += data & 0b111;
		} else if (data & COMMAND_WAIT) {
			// 1 byte [CCWWWWWW]: CC: command, WWWWWW: wait
			nextBeat += data & 0b00111111;
		} else if (data & COMMAND_VOLUME) {
			// 2 bytes [CCCHHHHH][VVVVVVVV]: CCC: command, HHHHHH: channelId, VVVVVVVV: volume
			setVolume(data & 0b00011111, pgm_read_byte(musicData++));
		} else if (data & COMMAND_TEMPO) {
			// 3 bytes [CCCCCCCC][TTTTTTTT][TTTTTTTT]: C: command, T: bpm increment counter
			bpmIncrementAt = pgm_read_byte(musicData++) << 8;
			bpmIncrementAt += pgm_read_byte(musicData++);
		} else {
			// COMMAND_END
			isMusicStopped = 1;
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
