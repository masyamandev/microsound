/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "common/sin.h"
#include "common/expnegshort.h"

void playHarp(waveChannel* channel, uint8_t data) {
	setChannelWave(sinTable, data);
	setChannelVolume(expNegShortTable, 1);
	channel->currentVolume = channel->instrumentVolume;
}
