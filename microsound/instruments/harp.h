/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "common/sin.h"
#include "common/expnegshort.h"

void playHarp(waveChannel* channel, uint8_t data) {
	channel->waveStep = pgm_read_word(&frequencies[data]);
	channel->waveForm = sinTable;

	channel->volumeForm = expNegShortTable;
	channel->volumeFormLength = 64;
	channel->volumeTicksPerSample = 1;

	channel->currentVolume = channel->instrumentVolume;
}
