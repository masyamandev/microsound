#include "common/sin.h"
#include "common/expneg.h"

void playSynthPiano(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[data]);
	channel->waveForm = sinTable;

	channel->volumeForm = expNegTable;
	channel->volumeFormLength = 255;
	channel->volumeTicksPerSample = 2;

	channel->currentVolume = channel->instrumentVolume;
}
