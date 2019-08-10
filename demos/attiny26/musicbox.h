/*
 * Simplified version of musicbox with 64 samples per period instead of 256
 */

#if SAMPLE_LENGTH != 64
#warning "Sound sample requires SAMPLE_LENGTH to be set to 64"
#endif

const int8_t musicboxWaveTable[] PROGMEM = {
		0,-11,-25,-41,-52,-59,-65,-72,
		-79,-86,-90,-90,-89,-89,-91,-92,
		-92,-91,-90,-89,-89,-88,-86,-82,
		-78,-75,-71,-66,-58,-51,-44,-37,
		-28,-16,-2,10,20,30,41,55,
		69,80,89,94,100,107,117,123,
		125,124,123,122,121,121,114,104,
		91,79,69,60,49,33,17,2
		};

const uint8_t musicboxVolumeTable[] PROGMEM = {
		255, 226, 199, 191, 184, 160, 163, 178, 177, 166, 158, 156, 147, 141, 135, 131,
		124, 118, 113, 107, 100, 95, 90, 85, 80, 75, 71, 67, 63, 59, 55, 51,
		48, 45, 43, 40, 39, 36, 34, 30, 28, 27, 25, 24, 23, 22, 22, 20,
		18, 18, 17, 16, 16, 15, 14, 14, 13, 12, 12, 11, 11, 10, 9, 9,
		8,7,6,5,4,3,2,1,0
		};
//
//const uint8_t musicboxVolumeTable[] PROGMEM = {
//		255,199,184,163,177,158,147,135,
//		124,113,100,90,80,71,63,55,
//		48,43,39,34,28,25,23,22,
//		18,17,16,14,13,12,11,9,
//		8,6,4,2,0};

void playMusicbox(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[data]) << 1; // transpose 1 octave up
	channel->waveForm = musicboxWaveTable;

	channel->volumeForm = musicboxVolumeTable;
	channel->volumeFormLength = 72 - 1;
	channel->volumeTicksPerSample = 4;
	channel->volumeTicksCounter = 4;

	channel->currentVolume = channel->instrumentVolume;
}
