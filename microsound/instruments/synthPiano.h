/*
 * Author: Aleksandr Maksymenko aka masyaman
 */

#include "common/sin.h"
#include "common/expneg.h"

void playSynthPiano(waveChannel* channel, uint8_t data) {
	setChannelWave(sinTable, data);
	setChannelVolume(expNegTable, 2);
	channel->currentVolume = channel->instrumentVolume;
}
