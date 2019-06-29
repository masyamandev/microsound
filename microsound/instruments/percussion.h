
#include "common/sin.h"
#include "common/expneg.h"


#define PERCUSSION_HAT_H 	0b00000000
#define PERCUSSION_HAT_L 	0b00000001
#define PERCUSSION_BAR_H 	0b00000010
#define PERCUSSION_BAR_L 	0b00000011

const int8_t barWaveTable[] PROGMEM = {
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
		-112, -115, -116, -116, -115, -113, -109, -103, -96, -88, -78, -67, -55, -41, -26, -11,
		4};// last value could be used for interpolation

//const uint8_t barVolumeSample1[] PROGMEM = {
////		127, 126, 126, 126, 126, 126, 125, 125, 124, 123, 123, 122, 121, 120, 119, 118,
////				117, 116, 114, 113, 112, 110, 108, 107, 105, 103, 102, 100, 98, 96, 94, 91,
////				89, 87, 85, 82, 80, 78, 75, 73,
//				70, 67, 65, 62, 59, 57, 54, 51,
//				48, 45, 42, 39, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3,
//				0
//};
//const uint8_t barVolumeSample[] PROGMEM = {
////		128, 113, 107, 98, 90, 82, 76, 69,
////		63, 58, 53, 49, 45, 41, 38, 34,
//		32, 29, 26, 24, 22, 20, 19, 17,
//		16, 14, 13, 12, 11, 10, 9, 8,
//		0};

//const uint8_t noiseVolumeH[] PROGMEM = {
//		100, 87, 77, 67, 59, 52, 45, 40, 35, 31, 27, 23, 21, 18, 16, 14,
//		12, 10, 9, 8, 7, 6, 5, 5, 4, 3, 3, 2, 2, 2, 2, 1,
//		0};

const uint8_t noiseVolumeH[] PROGMEM = {
		255, 214, 180, 151, 127, 107, 90, 75, 63, 53, 45, 37, 31, 26, 22, 18,
		15, 13, 11, 9, 7, 6, 5, 4, 3, 3, 2, 2, 1, 1, 1, 1,
		0};

const uint8_t noiseVolumeL[] PROGMEM = {
		128, 112, 98, 86, 76, 66, 58, 51, 45, 39, 34, 30, 26, 23, 20, 18,
		16, 14, 12, 10, 9, 8, 7, 6, 5, 4, 4, 3, 3, 2, 2, 2,
		0};

const uint8_t barVolumeH[] PROGMEM = {
		64, 56, 48, 40, 32, 24, 16, 8, //45, 43, 41, 39, 38, 36, 34, 33,
//		64, 61, 58, 56, 53, 51, 49, 47, //45, 43, 41, 39, 38, 36, 34, 33,
//		32, 30, 29, 28, 26, 25, 24, 23, //22, 21, 20, 19, 19, 18, 17, 16,
//		8, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2,
		0};

const uint8_t barVolumeL[] PROGMEM = {
		32, 24, 16, 8,// 8, 5,
//		32, 22, 16, 11,// 8, 5,
//		64, 45, 32, 22, 16, 11,// 8, 5,
//		64, 56, 49, 43, 38, 33, 29, 25, //22, 19, 17, 15, 13, 11, 10, 9,
//		32, 28, 24, 21, 19, 16, 14, 12,
		0};

void playPercussion(waveChannel* channel, uint8_t data) {

//	playNoise(expNegTable + (data & 0b00111111), 64, channel->instrumentVolume);

	if (data & 0b00000001) {
		playNoise(noiseVolumeH, 32, channel->instrumentVolume);
	} else {
		playNoise(noiseVolumeL, 32, channel->instrumentVolume);
	}

	if (data == PERCUSSION_BAR_H) {
		channel->waveStep = freqStep(55.000);
		channel->waveForm = sinTable;

		channel->volumeForm = barVolumeH;
		channel->volumeFormLength = 8;
		channel->volumeTicksPerSample = 4;
		channel->volumeTicksCounter = 4;

		channel->currentVolume = channel->instrumentVolume;
	} else if (data == PERCUSSION_BAR_L) {
		channel->waveStep = freqStep(55.000);
		channel->waveForm = sinTable;

		channel->volumeForm = barVolumeL;
		channel->volumeFormLength = 4;
		channel->volumeTicksPerSample = 4; // TODO increase?
		channel->volumeTicksCounter = 4;

		channel->currentVolume = channel->instrumentVolume;
	} else {
		channel->currentVolume = 0;
	}
}
