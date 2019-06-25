
// WARN: this instrument may require two channels

#define OVERDRIVE_SHORT 	0b10000000 // This bit indicates short play and mute

const int8_t overdrivenGuitarWaveTable[] PROGMEM = {
		0, -37, -57, -47, -15, 21, 47, 52, 37, 12, -11, -25, -27, -22, -17, -16,
		-21, -30, -38, -44, -45, -44, -43, -44, -47, -52, -56, -60, -60, -47, -17, 23,
		57, 69, 51, 15, -23, -46, -48, -31, -6, 14, 21, 6, -31, -80, -117, -127,
		-103, -61, -19, 3, 2, -17, -43, -63, -70, -67, -58, -51, -46, -33, -5, 31,
		61, 67, 49, 14, -20, -39, -37, -19, 4, 24, 32, 31, 25, 21, 21, 26,
		34, 41, 44, 44, 43, 41, 42, 43, 37, 12, -26, -63, -81, -70, -36, 2,
		30, 36, 22, -2, -25, -37, -39, -33, -26, -24, -28, -36, -44, -48, -49, -45,
		-31, -1, 39, 73, 85, 69, 33, -4, -28, -31, -15, 8, 24, 15, -20, -70,
		-107, -113, -85, -39, 2, 23, 17, -6, -34, -54, -59, -52, -42, -33, -23, -1,
		32, 65, 82, 73, 44, 8, -18, -25, -13, 9, 31, 44, 47, 42, 37, 35,
		38, 45, 52, 57, 58, 56, 55, 54, 56, 58, 53, 30, -8, -48, -69, -60,
		-29, 10, 40, 48, 35, 10, -13, -27, -29, -24, -17, -15, -19, -27, -34, -40,
		-41, -39, -37, -37, -39, -43, -47, -51, -53, -53, -53, -53, -55, -56, -58, -59,
		-52, -30, 7, 48, 71, 66, 37, 0, -30, -41, -30, -6, 17, 32, 37, 32,
		27, 24, 28, 35, 43, 49, 51, 50, 48, 48, 50, 54, 59, 62, 65, 65,
		66, 66, 67, 69, 71, 73, 74, 74, 75, 75, 76, 76, 77, 76, 67, 41,
		0};// last value could be used for interpolation

const uint8_t overdrivenGuitarVolumeTableLong[] PROGMEM = {
		147, 212, 211, 208, 205, 205, 208, 223, 224, 218, 220, 219, 214, 213, 207, 208,
		210, 221, 226, 216, 208, 206, 208, 216, 220, 215, 207, 207, 213, 218, 230, 233,
		233, 231, 239, 248, 232, 236, 234, 225, 215, 205, 203, 210, 211, 218, 211, 201,
		201, 204, 192, 190, 201, 213, 213, 209, 210, 220, 225, 222, 227, 221, 212, 208,
		201, 208, 214, 220, 235, 248, 255, 240, 240, 243, 248, 214, 205, 209, 207, 208,
		186, 191, 180, 177, 179, 176, 176, 177, 178, 175, 175, 174, 176, 178, 189, 208,
		220, 247, 244, 244, 242, 231, 224, 231, 233, 239, 227, 228, 221, 220, 199, 180,
		166, 161, 161, 155, 154, 153, 149, 157, 157, 155, 149, 147, 149, 165, 171, 184,
		191, 204, 215, 212, 213, 204, 200, 194, 197, 188, 188, 180, 184, 177, 183, 180,
		185, 183, 187, 190, 190, 191, 189, 186, 191, 183, 181, 175, 174, 172, 168, 162,
		158, 156, 151, 141, 140, 138, 134, 130, 128, 130, 124, 125, 122, 122, 122, 119,
		120, 119, 122, 122, 121, 122, 122, 120, 121, 117, 117, 116, 119, 116, 112, 110
		};
const uint8_t overdrivenGuitarVolumeTableShort[] PROGMEM = {
		164, 177, 180, 198, 235, 255, 217, 229, 221, 205, 190, 170, 153, 125, 117, 64,
		0};



void playOverdrivenGuitar(soundChannel* channel, uint8_t data) {
	channel->waveStep = frequencies[(data & 0b00111111)];
	channel->waveForm = overdrivenGuitarWaveTable;

	if (data & OVERDRIVE_SHORT) {
		channel->volumeForm = overdrivenGuitarVolumeTableShort;
		channel->volumeFormLength = 16;
		channel->volumeSample = 0;
		channel->volumeTicksPerSample = 1;
		channel->volumeTicksCounter = 1;
	} else {
		channel->volumeForm = overdrivenGuitarVolumeTableLong;
		channel->volumeFormLength = 192 - 1;
		channel->volumeSample = 0;
		channel->volumeTicksPerSample = 8;
		channel->volumeTicksCounter = 8;
	}

	channel->currentVolume = (channel->instrumentVolume) * 147 >> 8;
}

// This instrument requires 2 channels
void playOverdrivenGuitarChord(soundChannel* channel, uint8_t data) {
	channel->waveStep = frequencies[(data & 0b00111111)];
	channel->waveForm = overdrivenGuitarWaveTable;

	if (data & OVERDRIVE_SHORT) {
		channel->volumeForm = overdrivenGuitarVolumeTableShort;
		channel->volumeFormLength = 16;
		channel->volumeSample = 0;
		channel->volumeTicksPerSample = 1;
		channel->volumeTicksCounter = 1;
	} else {
		channel->volumeForm = overdrivenGuitarVolumeTableLong;
		channel->volumeFormLength = 192 - 1;
		channel->volumeSample = 0;
		channel->volumeTicksPerSample = 8;
		channel->volumeTicksCounter = 8;
	}

	channel->currentVolume = (channel->instrumentVolume) * 147 >> 8;

	// Play chord on next channel
	channel++;

	channel->waveStep = frequencies[(data & 0b00111111) + 7];
	channel->waveForm = overdrivenGuitarWaveTable;

	if (data & OVERDRIVE_SHORT) {
		channel->volumeForm = overdrivenGuitarVolumeTableShort;
		channel->volumeFormLength = 16;
		channel->volumeSample = 0;
		channel->volumeTicksPerSample = 1;
		channel->volumeTicksCounter = 1;
	} else {
		channel->volumeForm = overdrivenGuitarVolumeTableLong;
		channel->volumeFormLength = 192 - 1;
		channel->volumeSample = 0;
		channel->volumeTicksPerSample = 8;
		channel->volumeTicksCounter = 8;
	}

	channel->currentVolume = (channel->instrumentVolume) * 147 >> 8;

}
