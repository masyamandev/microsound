/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

const int8_t musicboxWaveTable[] PROGMEM = {
		0, -5, -11, -18, -25, -33, -41, -46, -52, -56, -59, -62, -65, -69, -72, -75,
		-79, -83, -86, -88, -90, -90, -90, -90, -89, -89, -89, -90, -91, -91, -92, -92,
		-92, -91, -91, -90, -90, -89, -89, -89, -89, -89, -88, -87, -86, -84, -82, -80,
		-78, -77, -75, -73, -71, -69, -66, -62, -58, -55, -51, -47, -44, -41, -37, -33,
		-28, -23, -16, -9, -2, 4, 10, 15, 20, 25, 30, 36, 41, 48, 55, 62,
		69, 75, 80, 85, 89, 91, 94, 96, 100, 103, 107, 112, 117, 120, 123, 125,
		125, 125, 124, 124, 123, 122, 122, 122, 121, 121, 121, 118, 114, 111, 104, 97,
		91, 85, 79, 73, 69, 65, 60, 54, 49, 41, 33, 25, 17, 9, 2, -2,
		-7, -11, -15, -19, -25, -31, -37, -44, -51, -57, -61, -65, -68, -70, -71, -73,
		-75, -77, -80, -83, -86, -87, -89, -90, -89, -88, -88, -88, -87, -88, -89, -90,
		-91, -92, -93, -92, -91, -91, -90, -89, -88, -88, -88, -87, -87, -86, -84, -81,
		-79, -77, -74, -72, -70, -69, -67, -64, -61, -57, -52, -48, -43, -38, -34, -30,
		-27, -22, -18, -13, -7, -1, 5, 10, 15, 20, 27, 34, 41, 48, 54, 59,
		63, 67, 70, 74, 77, 82, 87, 92, 98, 104, 108, 112, 115, 116, 117, 118,
		118, 119, 120, 122, 124, 125, 126, 127, 125, 123, 121, 116, 111, 106, 101, 96,
		91, 87, 83, 79, 74, 69, 62, 55, 47, 40, 32, 24, 19, 14, 9, 4
		};

const uint8_t musicboxVolumeTable[] PROGMEM = {
	    255, 226, 199, 191, 184, 160, 163, 178, 177, 166, 158, 156, 147, 141, 135, 131,
	    124, 118, 113, 107, 100, 95, 90, 85, 80, 75, 71, 67, 63, 59, 55, 51,
	    48, 45, 43, 40, 39, 36, 34, 30, 28, 27, 25, 24, 23, 22, 22, 20,
	    18, 18, 17, 16, 16, 15, 14, 14, 13, 12, 12, 11, 11, 10, 9, 9,
	    8,7,6,5,4,3,2,1,0};

void playMusicbox(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[data]);
	channel->waveForm = musicboxWaveTable;

	channel->volumeForm = musicboxVolumeTable;
	channel->volumeFormLength = 72 - 1;
	channel->volumeTicksPerSample = 4;
	channel->volumeTicksCounter = 4;

	channel->currentVolume = channel->instrumentVolume;
}
