#ifndef MICROMUSIC_INIT
#define MICROMUSIC_INIT

/*
 * Control flow of music data and translate this data to sound generator.
 *
 * Simplified usage:
 * initMusic(); // Init music data and sound control
 * sei(); // Enable interrupts, silence sound should be generated
 * setSample(0, instrument1); // Use instrument1 as sample 0
 * setSample(1, instrument2); // Init all other instruments...
 *
 * playMusic(mySong); // Start playing music at pointer mySong
 * while (!isMusicStopped) fillMusicBuffer(); // Fill music buffer in loop
 *
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "microsound.h"


typedef void (*sampleSource)(waveChannel* channel, uint8_t data);

// SAMPLES_SIZE - amount of different instruments
// CHANNELS_SIZE - amount of simultaneously played channels, managed by microsound.h
sampleSource samples[SAMPLES_SIZE];
sampleSource channelSamples[CHANNELS_SIZE];

const uint8_t *musicData;
uint16_t nextBeat;
uint8_t isMusicStopped;


// Init music and sound
inline void initMusic() {
	initSound();
	nextBeat = 0;
	isMusicStopped = 1;
}

// Assign instrument to specific id
inline void setSample(uint8_t id, sampleSource sample) {
	samples[id] = sample;
}

#include "commands.h"

// Update channels data from music array
INLINE_BUFFER_FILL
void updateMusicData() {
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
}

// Fill buffer until it's full
inline void fillMusicBuffer() {
	// Smaller value requires bigger overhead for writing remain of the buffer
	while ((samplesToWrite) > 4) {
		fillBuffer(SAMPLES_PER_TICK);
		updateMusicData();
	}
}

// Play music data from specified array
INLINE_SOUND_CONTROL void playMusic(const uint8_t *data) {
	resetSound();
	musicData = data;
	nextBeat = 0;
	isMusicStopped = 0;
}

inline void stopMusic() {
	isMusicStopped = 1;
}

#endif
