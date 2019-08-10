/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

const int8_t harmonicaWaveTable[] PROGMEM = {
		0, -11, -29, -39, -39, -37, -37, -45, -53, -53, -49, -43, -34, -24, -22, -17,
		-6, 6, 22, 39, 55, 69, 72, 72, 76, 78, 83, 85, 81, 79, 74, 63,
		52, 47, 36, 17, 0, -19, -33, -40, -42, -48, -60, -75, -86, -94, -98, -95,
		-87, -75, -66, -55, -43, -27, -13, -2, 9, 18, 25, 31, 36, 40, 45, 48,
		44, 36, 26, 19, 13, 7, 3, -4, -14, -26, -40, -51, -56, -61, -72, -78,
		-77, -77, -77, -73, -67, -61, -57, -52, -42, -31, -20, -9, 1, 10, 17, 27,
		37, 44, 50, 52, 52, 50, 49, 50, 51, 45, 31, 14, 2, 0, -4, -13,
		-20, -24, -30, -32, -28, -26, -27, -22, -16, -10, 0, 14, 27, 30, 28, 26,
		27, 33, 34, 34, 40, 42, 36, 33, 39, 41, 32, 22, 12, 5, 1, -1,
		-1, -6, -13, -14, -15, -16, -16, -20, -24, -27, -26, -24, -19, -14, -12, -13,
		-11, -12, -14, -15, -18, -23, -30, -35, -36, -35, -39, -46, -49, -52, -57, -63,
		-68, -65, -56, -50, -50, -51, -41, -28, -18, -12, -8, -2, 2, 5, 13, 25,
		34, 37, 37, 35, 34, 35, 36, 30, 18, 7, 0, -7, -14, -18, -20, -26,
		-36, -44, -48, -48, -47, -44, -37, -32, -26, -17, -7, 5, 18, 32, 50, 70,
		91, 111, 127, 124, 106, 87, 70, 64, 58, 54, 59, 53, 35, 20, 12, 1,
		-2, 12, 21, 22, 22, 27, 33, 33, 35, 45, 46, 34, 24, 17, 7, 3,
		0};// last value could be used for interpolation

const uint8_t harmonicaVolumeTable[] PROGMEM = {
		16, 86, 142, 177, 199, 212, 220, 224, 225, 226, 225, 224, 222, 220, 218, 216,
		};

void playHarmonica(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[data - 12]);
	channel->waveForm = harmonicaWaveTable;

	channel->volumeForm = harmonicaVolumeTable;
	channel->volumeFormLength = 16 - 1;
	channel->volumeTicksPerSample = 1;
	channel->volumeTicksCounter = 1;

	channel->currentVolume = 0;
}
