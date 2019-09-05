/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "common/expneg.h"

const int8_t overdrivenGuitarWaveTable[] PROGMEM = {
		0, 3, 6, 6, 3, -2, -14, -29, -43, -55, -64, -69, -69, -65, -59, -52,
		-45, -41, -38, -39, -42, -48, -55, -63, -70, -75, -77, -78, -77, -75, -71, -68,
		-66, -65, -66, -68, -71, -75, -79, -83, -86, -88, -89, -89, -88, -86, -85, -84,
		-84, -84, -85, -87, -89, -92, -94, -96, -97, -98, -98, -97, -97, -96, -96, -96,
		-96, -97, -98, -99, -98, -95, -90, -82, -73, -65, -58, -53, -52, -54, -57, -62,
		-68, -73, -76, -78, -78, -76, -72, -68, -64, -60, -58, -57, -57, -59, -62, -64,
		-67, -69, -69, -69, -68, -66, -64, -62, -60, -58, -57, -57, -56, -54, -50, -43,
		-35, -26, -18, -12, -10, -9, -11, -14, -19, -23, -26, -28, -28, -26, -23, -19,
		-15, -11, -8, -6, -4, -4, -4, -3, -3, -1, 0, 4, 7, 11, 15, 19,
		21, 22, 32, 39, 44, 45, 44, 40, 35, 30, 26, 24, 24, 26, 30, 35,
		40, 45, 50, 54, 58, 65, 73, 81, 89, 94, 97, 99, 98, 96, 94, 91,
		89, 89, 90, 92, 95, 99, 103, 107, 110, 112, 113, 113, 113, 112, 111, 111,
		111, 111, 113, 115, 117, 120, 122, 124, 125, 126, 127, 125, 122, 116, 107, 96,
		87, 80, 76, 76, 79, 84, 91, 98, 103, 107, 108, 107, 100, 90, 76, 60,
		47, 38, 33, 32, 36, 44, 52, 61, 68, 72, 73, 70, 65, 58, 51, 44,
		39, 36, 35, 36, 37, 36, 32, 25, 16, 8, 1, -3, -6, -7, -5, -2
		};

void playOverdrivenGuitar(waveChannel* channel, uint8_t data) {
	setChannelWave(overdrivenGuitarWaveTable, (data & 0b00111111));
	setChannelVolume(expNegTable, 8);
	channel->currentVolume = channel->instrumentVolume;

}
