#include "common/sin.h"
#include "common/expneg.h"

void playSynthPiano(soundChannel* channel, uint8_t data) {
	channel->waveStep = frequencies[data];
	channel->waveForm = sinTable;

	channel->volumeForm = expNegTable;
	channel->volumeFormLength = 255;
	channel->volumeSample = 0;
	channel->volumeTicksPerSample = 2;

	channel->currentVolume = channel->instrumentVolume;
}
