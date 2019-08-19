/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "common/expneg.h"

#define OVERDRIVE_SHORT 	0b10000000 // This bit indicates short play and mute

const int8_t overdrivenGuitarChordWaveTable[] PROGMEM = {
		0, 0, -5, -26, -47, -37, -23, -35, -51, -52, -58, -58, -51, -53, -74, -80,
		-74, -81, -93, -91, -84, -86, -93, -90, -82, -80, -85, -88, -87, -81, -66, -60,
		-63, -59, -49, -49, -55, -49, -37, -32, -22, -16, -17, -14, -6, -1, 5, 17,
		25, 49, 44, 35, 39, 49, 66, 77, 86, 94, 101, 107, 115, 124, 127, 120,
		105, 110, 124, 122, 100, 92, 98, 98, 96, 95, 71, 56, 65, 72, 49, 30,
		28, 24, 13, 9, 13, 12, 3, -15, -38, -48, -39, -27, -27, -35, -32, -30,
		-38, -41, -40, -46, -55, -57, -57, -57, -45, -37, -46, -58, -61, -55, -45, -37,
		-34, -26, -32, -35, -33, -30, -18, -13, -13, -9, -2, 3, 5, 4, 4, 3,
		-5, -2, 4, -1, -18, -11, 5, 2, -11, -14, -19, -14, 1, 12, -3, -12,
		-9, -12, -16, -11, -5, -8, -12, -10, -10, -14, -25, -31, -26, -18, -4, -8,
		-23, -19, -3, 0, -12, -21, -18, -15, -10, -8, -11, -8, -5, -16, -22, -10,
		1, 16, 5, -4, 0, 8, 19, 19, 17, 24, 35, 40, 42, 45, 47, 42,
		27, 29, 46, 52, 36, 33, 40, 36, 32, 35, 24, 17, 24, 23, 1, -7,
		4, 6, -1, -1, 5, 6, -1, -11, -17, -19, -12, 0, 7, 4, 7, 7,
		3, 7, 21, 23, 13, 7, 9, 17, 33, 41, 32, 21, 19, 19, 22, 25,
		23, 32, 30, 27, 23, 12, 19, 30, 36, 36, 30, 24, 22, 18, 13, 9
		};

const uint8_t overdrivenGuitarChordVolumeTableShort[] PROGMEM = {
		255, 248, 244, 238, 233, 228, 223, 219, 214, 209, 205, 200, 196, 192, 128, 64,
		0};

#ifdef ADD_GUITAR_NOISE
const uint8_t overdrivenGuitarChordNoiseVolume[] PROGMEM = {
		64, 96, 96, 64, 32, 16, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		64, 96, 96, 64, 32, 16, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		64, 96, 96, 64, 32, 16, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0};
#endif

void playOverdrivenGuitarChord(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[(data & 0b00111111) - 12]);
	channel->waveForm = overdrivenGuitarChordWaveTable;

	if (data & OVERDRIVE_SHORT) {
		channel->volumeForm = overdrivenGuitarChordVolumeTableShort;
		channel->volumeFormLength = 16;
		channel->volumeTicksPerSample = 1;
		channel->volumeTicksCounter = 1;
	} else {
		channel->volumeForm = expNegTable;
		channel->volumeFormLength = 64;
		channel->volumeTicksPerSample = 8;
		channel->volumeTicksCounter = 8;
	}

	channel->currentVolume = channel->instrumentVolume;

#ifdef ADD_GUITAR_NOISE
	playNoise(overdrivenGuitarNoiseVolume, 48, channel->instrumentVolume);
#endif
}
