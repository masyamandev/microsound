
#include "common/sin.h"
#include "common/expneg.h"


#define PERCUSSION_HAT_H 	0b00000000
#define PERCUSSION_HAT_L 	0b00000001
#define PERCUSSION_BAR_H 	0b00000010
#define PERCUSSION_BAR_L 	0b00000011

#ifndef BAR_VOLUME_SKIP
#define BAR_VOLUME_SKIP		24
#endif
#define BAR_L_VOLUME_SKIP		8
#define BAR_VOLUME_LENGTH		64


const uint8_t noiseVolumeH[] PROGMEM = {
	    102, 89, 78, 69, 60, 53, 46, 41, 36, 31, 27, 24, 21, 18, 16, 14,
	    12, 11, 9, 8, 7, 6, 5, 5, 4, 3, 3, 3, 2, 2, 2, 1,
		0};

const uint8_t noiseVolumeM[] PROGMEM = {
	    153, 129, 108, 91, 76, 64, 54, 45, 38, 32, 27, 22, 19, 16, 13, 11,
	    9, 8, 6, 5, 4, 4, 3, 2, 2, 2, 1, 1, 1, 1, 0, 0,
		0};

const uint8_t noiseVolumeL[] PROGMEM = {
	    51, 43, 36, 30, 25, 21, 18, 15, 12, 10, 9, 7, 6, 5, 4, 3,
	    3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0};

const uint8_t barVolume[] PROGMEM = {
		184, 176, 168, 161, 154, 148, 141, 135, 130, 124, 119, 114, 109, 104, 100, 96,
		92, 88, 84, 80, 77, 74, 70, 67, 65, 62, 59, 57, 54, 52, 50, 48,
		46, 44, 42, 40, 38, 37, 35, 33, 32, 31, 29, 28, 27, 26, 25, 24,
		23, 22, 21, 20, 19, 18, 17, 16, 16, 15, 14, 14, 13, 13, 12, 12,
//		11, 11, 10, 10, 9, 9, 8, 8, 8, 7, 7, 7, 6, 6, 6, 6,
//		5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3,
//		2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1,
//		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0};

void playPercussion(waveChannel* channel, uint8_t data) {

	if (data == PERCUSSION_BAR_H) {
		playNoise(noiseVolumeM, 32, channel->instrumentVolume);

		channel->waveStep = freqStep(55.000);
		channel->waveForm = sinTable;

		channel->volumeForm = barVolume + BAR_VOLUME_SKIP;
		channel->volumeFormLength = BAR_VOLUME_LENGTH - BAR_VOLUME_SKIP;
		channel->volumeTicksPerSample = 2;
		channel->volumeTicksCounter = 2;

		channel->currentVolume = channel->instrumentVolume;
	} else if (data == PERCUSSION_BAR_L) {
		playNoise(noiseVolumeL, 32, channel->instrumentVolume);

		channel->waveStep = freqStep(55.000);
		channel->waveForm = sinTable;

		channel->volumeForm = barVolume + BAR_L_VOLUME_SKIP + BAR_VOLUME_SKIP;
		channel->volumeFormLength = BAR_VOLUME_LENGTH - BAR_L_VOLUME_SKIP - BAR_VOLUME_SKIP;
		channel->volumeTicksPerSample = 1;
		channel->volumeTicksCounter = 1;

		channel->currentVolume = channel->instrumentVolume;
	} else if (data == PERCUSSION_HAT_H) {
		playNoise(noiseVolumeH, 32, channel->instrumentVolume);
		channel->currentVolume = 0;
	} else {
		playNoise(noiseVolumeL, 32, channel->instrumentVolume);
		channel->currentVolume = 0;
	}
}
