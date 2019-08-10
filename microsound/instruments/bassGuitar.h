/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "common/expneg.h"

const int8_t bassGuitarWaveTable[] PROGMEM = {
		4, 19, 33, 47, 60, 72, 83, 92, 101, 108, 114, 119, 122, 125, 126, 127,
		126, 125, 123, 120, 116, 112, 108, 103, 98, 92, 87, 81, 75, 70, 64, 59,
		54, 49, 44, 40, 36, 32, 29, 25, 23, 20, 18, 16, 14, 13, 11, 10,
		8, 7, 6, 5, 3, 2, 1, 0, -1, -2, -4, -5, -6, -7, -9, -10,
		-11, -11, -12, -13, -13, -13, -13, -14, -14, -13, -13, -13, -12, -12, -12, -11,
		-11, -10, -9, -9, -8, -8, -7, -6, -5, -4, -4, -3, -2, -1, 0, 0,
		0, 1, 2, 2, 3, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		4, 3, 3, 2, 1, 1, 0, 0, -1, -2, -3, -4, -4, -5, -6, -6,
		-7, -7, -7, -7, -7, -7, -7, -6, -6, -6, -5, -5, -4, -4, -3, -3,
		-2, -2, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, -1, -1, -1, -1, -2, -2, -2, -3, -3, -3, -3,
		-3, -3, -3, -3, -3, -2, -2, -2, -1, -1, -1, 0, 0, 0, -1, -1,
		-2, -3, -4, -5, -7, -8, -10, -12, -14, -16, -18, -20, -21, -23, -24, -25,
		-26, -26, -26, -26, -25, -24, -23, -22, -20, -19, -17, -16, -16, -16, -17, -18,
		-20, -23, -27, -31, -36, -42, -49, -56, -63, -70, -78, -85, -92, -98, -104, -108,
		-112, -115, -116, -116, -115, -113, -109, -103, -96, -88, -78, -67, -55, -41, -26, -11
		};// last value could be used for interpolation

void playBassGuitar(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[data]);
	channel->waveForm = bassGuitarWaveTable;

	channel->volumeForm = expNegTable;
	channel->volumeFormLength = 256 - 1;
	channel->volumeTicksPerSample = 4;
	channel->volumeTicksCounter = 4;

	channel->currentVolume = channel->instrumentVolume;
}
