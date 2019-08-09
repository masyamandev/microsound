/*
 * Simplified version of musicbox with 64 samples per period instead of 256
 */

const int8_t musicboxWaveTable[] PROGMEM = {
		0, -25, -52, -65,
		-79, -90, -89,  -91,
		-92, -90, -89, -86,
		-78, -71, -58, -44,
		-28, -2, 20, 41,
		69, 89, 100, 117,
		125, 123, 121, 114,
		91, 69, 49, 17,
		-7, -25, -51, -68,
		-75, -86, -89, -87,
		-91, -91, -88, -87,
		-79, -70, -61, -43,
		-27, -7, 15, 41,
		63, 77, 98, 115,
		118, 124, 125, 111,
		91, 74, 47,  19
		};

const uint8_t musicboxVolumeTable[] PROGMEM = {
	    255, 226, 199, 191, 184, 160, 163, 178, 177, 166, 158, 156, 147, 141, 135, 131,
	    124, 118, 113, 107, 100, 95, 90, 85, 80, 75, 71, 67, 63, 59, 55, 51,
	    48, 45, 43, 40, 39, 36, 34, 30, 28, 27, 25, 24, 23, 22, 22, 20,
	    18, 18, 17, 16, 16, 15, 14, 14, 13, 12, 12, 11, 11, 10, 9, 9,
	    8,7,6,5,4,3,2,1,0};

//const uint8_t musicboxVolumeTable[] PROGMEM = {
////	    255, 184, 177, 147,
//	    124, 100, 80, 63,
//	    48, 39, 28, 23,
//	    18, 16, 13, 11,
//	    8,4,0};

void playMusicbox(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[data]);
	channel->waveForm = musicboxWaveTable;

	channel->volumeForm = musicboxVolumeTable;
	channel->volumeFormLength = 72 - 1;
	channel->volumeTicksPerSample = 4;
	channel->volumeTicksCounter = 4;

	channel->currentVolume = channel->instrumentVolume;
}
