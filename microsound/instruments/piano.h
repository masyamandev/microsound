#include "common/expneg.h"

const int8_t pianoWaveTable[] PROGMEM = {
		0, 1, 3, 7, 12, 17, 24, 31, 38, 44, 50, 55, 58, 60, 60, 59,
		56, 52, 49, 45, 43, 42, 43, 45, 48, 50, 51, 52, 51, 48, 45, 40,
		36, 31, 26, 21, 16, 11, 6, 3, 0, -1, -3, -5, -8, -11, -15, -19,
		-24, -28, -31, -34, -35, -36, -34, -30, -26, -20, -15, -10, -6, -4, -2, 4,
		10, 17, 21, 25, 27, 29, 31, 32, 32, 31, 29, 27, 24, 23, 24, 26,
		30, 34, 38, 41, 44, 47, 50, 54, 58, 65, 72, 80, 88, 96, 104, 111,
		118, 122, 125, 127, 125, 123, 119, 115, 109, 104, 98, 92, 86, 80, 75, 70,
		67, 64, 61, 58, 55, 50, 46, 42, 38, 35, 33, 32, 32, 31, 30, 29,
		28, 25, 22, 18, 13, 7, 0, -5, -10, -13, -13, -12, -10, -8, -6, -5,
		-6, -8, -12, -17, -24, -31, -38, -44, -48, -50, -51, -50, -48, -45, -41, -37,
		-33, -30, -27, -26, -26, -28, -30, -33, -36, -40, -43, -46, -50, -53, -56, -59,
		-61, -64, -67, -70, -72, -73, -73, -72, -71, -68, -64, -60, -55, -50, -45, -41,
		-39, -38, -37, -37, -38, -39, -40, -41, -41, -42, -43, -43, -45, -47, -49, -53,
		-58, -62, -67, -71, -73, -74, -74, -71, -66, -59, -52, -44, -37, -31, -27, -24,
		-24, -26, -29, -34, -40, -46, -53, -59, -65, -68, -70, -69, -66, -62, -56, -50,
		-44, -39, -36, -33, -31, -29, -26, -22, -17, -12, -8, -5, -3, -2, -1, -1,
		0};// last value could be used for interpolation

//const uint8_t pianoVolumeTable[] PROGMEM = {
//		255, 230, 218, 190, 196, 219, 239, 243, 255, 250, 244, 248, 239, 231, 224, 213,
//		225, 218, 210, 204, 191, 206, 199, 190, 186, 189, 194, 183, 173, 174, 180, 173,
//		172, 164, 158, 159, 154, 156, 150, 142, 147, 144, 143, 135, 130, 133, 131, 130,
//		120, 115, 115, 118, 112, 105, 102, 103, 106, 99, 98, 97, 95, 96, 90, 88,
//		83, 83, 83, 77, 74, 70, 72, 70, 68, 66, 62, 63, 61, 60, 57, 54,
//		52, 52, 52, 49, 46, 44, 44, 43, 42, 40, 39, 38, 36, 35, 34, 33,
//		33, 32, 31, 31, 30, 28, 26, 26, 27, 26, 26, 25, 24, 24, 24, 24,
//		23, 23, 23, 23, 23, 21, 21, 22, 22, 22, 21, 20, 20, 21, 20, 20,
//		20, 20, 20, 19, 20, 19, 19, 20, 19, 20, 19, 19, 19, 19, 19, 18,
//		17, 17, 17, 16, 15, 14, 14, 14, 13, 12, 11, 11, 11, 10, 10, 9,
//		8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 1, 1, 0};

void playPiano(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[data]);
	channel->waveForm = pianoWaveTable;

	channel->volumeForm = expNegTable;//pianoVolumeTable;
//	channel->volumeForm = pianoVolumeTable;
//	channel->volumeFormLength = 175 - 1;
	channel->volumeFormLength = 256 - 1;
	channel->volumeTicksPerSample = 4;
	channel->volumeTicksCounter = 4;

	channel->currentVolume = (channel->instrumentVolume) * 142 >> 8;
}
